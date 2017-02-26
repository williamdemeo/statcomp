/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  gn.c

  Created on 12/18/97 by William J. De Meo
    Last modified 12/21/97

  Purpose: Perform one iteration of Gauss-Newton with step halving
           
  Further Details:  This implementation uses BLAS 2
                    (matrix-vector mult. and rank 1 updates)

  Dependencies:                   
  subroutines found in:
              /accounts/grad/chip/lib/decomp/QR/House.c
              sunperf, and blas
              the later two are linked with the options:
              -lsunperf -dalign -lblas
              compilation must be done with the -dalign option
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <math.h>

/* ~~~Prototypes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For subroutines in /accounts/grad/chip/lib/decomp/QR/House.c:            */
#include "prototypes.h"

/* 
For BLAS subroutines:            */
 
double dnrm2_(long *N, double *x, long *INC);/* L2 norm of x*/
void dcopy_(long *N, double *X, long *INCX, double *Y, long *INCY); /* y <- x */

/* y <- (alpha)Ax + (beta)y   (or A^t if TRANSA='T') */
void dgemv_(char *TRANSA, long *M, long *N, double *alpha, double *A, long *LDA, 
            double *x, long *INCX, double *beta, double *y, long *INCY);

/* C <- (alpha)AB + (beta)C   */
void dgemm_(char *TRANSA, char *TRANSB, long *M, long *N, long *K, double *alpha, 
            double *A, long *LDA, double *B, long *LDB, double *beta, double *C,long *LDC); 

/* B <- alpha*inv(A)*B */
void dtrsm_(char *SIDE, char *UPLO, char *TRANSA, char *DIAG, long *M, long *N,
            double *alpha, double *A, long *LDA, double *B, long *LDB);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void reg(long M, long N, double *QR, double *leadu, double *E, 
         double *y, double *B, double *cov, double *se, double *e, double *sigma);

void read_name(char *);

void Exit(int i,long k);
void Free(double*,double*,double*,double*,double*,double*,double*,double*);

/* Tolerance for smallest singular value of J */
#define SINGTOL 1.0e-7
#define DELTOL 1.0e-7 
#define STEPTOL 1.0e-4 

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Subroutine gn:

   Arguments: 
              M  (long) number of rows of X

              N  (long) number of columns of X

              X  (pointer to double) the M by N matrix of covariates
              
              Y  (pointer to double) M by 1 observable vector

              P  (long) number of parameters
                 
              theta (pointer to double) P-vector of parameters
                    on entry: initial guess
                    on exit: improved solution after one iteration

              (*f)(M,N,X,P,theta,F) points to a function which evaluates to the expectation 
                               surface for given covariates X and parameter values theta

              (*g)(M,N,X,P,theta,J) points to a function which evaluates to the analytic 
                               Jacobian of f

              cov   on entry: an arbitrary PxP matrix
                    on exit: the estimated asymptotic covariance matrix

              sigma   on exit: the mse =  |y - f(theta)|^2 / (M-P)
              
              iter (long) max number of iterations
              
*/
void gn(long M, long N, double *X, double *Y, long P, double *theta,
        void   (*f)(long M, long N, double *X, long P, double *theta, double *F), 
        void   (*g)(long M, long N, double *X, long P, double *theta, double *J),
        double *cov, double *sigma, long iter)
{
     long i,j,k, one=(long)1;
     double *F, *J, *leadu, *E, *z, *delta, newS, oldS, half;
     double *pwork,*ework,test;
     
  
     F = dmalloc(M);
     J = dmalloc(M*P);
     z = dmalloc(M);
     E = dmalloc(P*P);  
     leadu = dmalloc(P);
     delta = dmalloc(P);

     pwork = dmalloc(P); /* parameter workspace */
     ework = dmalloc(M); /* error workspace */

     for(k=0;k<iter;k++)
     {
          (*f)(M,N,X,P,theta,F);
          /* z <- y - f(theta) */
          for(i=0;i<M;i++) z[i] = Y[i] - F[i];

          oldS = dnrm2_(&M,z,&one); /* L2 norm of error */

          /* Form Jacobian and QR decomposition */
          (*g)(M,N,X,P,theta,J); 

          qrpivot(M,P,J,E,leadu); 
          /*printf("\nJ[%d] = \n",k+1);
            matprint(J,M,P);*/

          if(fabs(J[M*(P-1)+(P-1)]) < SINGTOL)
          {
               Exit(0,k); /* 0 <= J rank defficient (bad exit) */
               Free(F,J,z,E,leadu,delta,pwork,ework);
               return;
          }
          
          /* reg for fitting z ~ J.delta */
          reg(M,P,J,leadu,E,z,delta,cov,pwork,ework,sigma);

          /* Don't need errors=pwork or se=ework computed by reg() */
          /* So P vector pwork and M vector ework are used
             for a different purpose below */

          /* cov = inv(J^tJ) for J corresponding to current theta 
             so if we exit with codes 1 or 2 below, i.e. before computing a new theta,
             we return the correct covariance matrix */

          test=(double)0;
          for(j=0;j<P;j++) 
          {
               if(fabs(delta[j])>test) test = delta[j];
          }
          if(test < DELTOL)   
          {
               *sigma = oldS/(M-P);      /* get new sigma before exit */
               Exit(1,k);                  /* 1 <= no change in theta_i */
               Free(F,J,z,E,leadu,delta,pwork,ework);
               return;
          }

          j=0;
          do
          {
               if((half = pow(.5,j)) < STEPTOL)
               {
                    *sigma = oldS/(M-P);      /* get new sigma before exit */
                    Exit(2,k);  /* 2 <= No improvements from steps */
                    Free(F,J,z,E,leadu,delta,pwork,ework);
                    return;
               }
               j++;
               /* compute new candidate coefficients */
               for(i=0;i<P;i++) pwork[i] = theta[i] + half*delta[i]; 
               (*f)(M,N,X,P,pwork,F); 
               for(i=0;i<M;i++) ework[i] = Y[i] - F[i];        /* compute new error */
               newS = dnrm2_(&M, ework, &one);  /* L2 norm of new error*/         
          }while(newS > oldS);

          dcopy_(&P,pwork, &one, theta, &one); /* theta <- pwork */
     }

}/*~~~ end gn() ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Subroutine reg()
   Arguments:
           
        M number of rows of X
 
        N number of columns of X (expect N < M)

        QR the result of applying qrpivot() to X
           (i.e. upper triangle is R, lower trapezoid are u's)

        leadu
              on entry: the vector of leading u's resulting from qrpivot()
              on exit: the vector of coefficient estimates B, where y = XB

        E the permutation matrix resulting from qrpivot()

        y  a vector (length M) of "observables" (the rhs in XB = y)

        B     on entry: an arbitrary length N vector
              on exit: the coefficient estimates
                     
        cov   on entry: an arbitrary NxN matrix
              on exit: the covariance matrix

        se    on entry: an arbitrary length N vector
              on exit: the s.e.'s of the coefficient estimates

        e     on entry: an arbitrary length M vector
              on exit: the vector of residuals:  e = y - XB
           
        sigma   on exit: the mse =  y^te / (M-N)
        */
        
void reg(long M, long N, double *QR, double *leadu, double *E, 
         double *y, double *B, double *cov, double *se, double *e, double *sigma)
{
     long i,j,mindim;
     double a, *Qy, *invR, *EiR, *coef;

     /* BLAS arguments */
     long INC=(long)1;
     double one = (double)1, zero = (double)0;
     char UPLO, NOTRANS, TRANS, DIAG, SIDE; 
     UPLO='U'; NOTRANS = 'N'; TRANS = 'T'; DIAG = 'N'; SIDE='L';
  
     dcopy_(&M, y, &INC, e, &INC);     /* e <- y */

     mindim = lmin(M-1,N);    /* expect mindim = N */

     /* Apply P(n)...P(1) to e to get e <- (Q_1 Q_2)^t Y*/
     for(j=0;j<mindim;j++)
     {
          a = leadu[j]*e[j];        /* initialize  a = u(1)e(1) */
          for(i=j+1;i<M;i++)
               a += QR[M*j+i]*e[i]; /* a = u^t e */
          a *= (double)(-2);
          e[j] += a * leadu[j];     /* e(1) <- e(1) - 2 u(1)u^te */
          for(i=j+1;i<M;i++)
               e[i] +=  a* QR[M*j+i]; /* e <- e + (-2)uu^t e */
     }
/*~~~~~~~~~~~~~~~~~~~~
  COMPUTE COEFFICIENTS
  
  /* compute inv(R) */
     invR = dmalloc(N*N);     /* workspace */
     for(j=0;j<N;j++)         /* begin with identity matrix */
     {
          for(i=0;i<N;i++)
               invR[N*j+i]=(double)0;
          invR[N*j+j]=(double)1;
     }
     /* invR <- one*inv(R)*invR = one*inv(R)*eye  */
     dtrsm_(&SIDE, &UPLO, &NOTRANS, &DIAG, &N, &N, &one, QR, &M,invR,&N);

     /* compute the E*inv(R) matrix */
     EiR = dmalloc(N*N);      
     /*  EiR <- (one)E*invR + (zero)EiR  */
     dgemm_(&NOTRANS, &NOTRANS, &N, &N, &N, &one, E, &N, 
            invR, &N, &zero, EiR, &N); 
     free(invR);

     /* compute the coefficients */
     dgemv_(&NOTRANS, &N, &N, &one, EiR, &N, e, &INC, &zero, B, &INC);
     /* B <- (one)EiR*e + (zero)B    (zero = 0)  only references 1st N elements of e */

/********* residuals and mse for the OLS part not necessary *********/     
     if(0)
     { 

          /*  COMPUTE RESIDUALS
           */
          for(i=0;i<N;i++) e[i]=(double)0; /* annihilate first N elements of e */

          /* Apply P(1)...P(n) to e  to get e <- Q2 Q2^t Y*/
          for(j=(mindim-1);j>=0;j--)
          {
               a = leadu[j]*e[j];        /* initialize  a = u(1)e(1) */
               for(i=j+1;i<M;i++)
                    a += QR[M*j+i]*e[i]; /* a = u^t e */
               a *= (double)(-2);
               e[j] += a * leadu[j];     /* e(1) <- e(1) - 2 u(1)u^te */
               for(i=j+1;i<M;i++)
                    e[i] +=  a* QR[M*j+i]; /* e <- e + (-2)uu^t e */
          }

          /*  COMPUTE MSE  (wrong MSE in nonlinear case. currently embraced by if(0))
           */
          *sigma = ddot_(&M, y, &INC, e, &INC);
          *sigma /= (M - N);

     } 
/*** end if(0) ***/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  COMPUTE COVARIANCE MATRIX and SE's

  cov <- (one)EiR*(EiR)' + (zero)cov  */
     dgemm_(&NOTRANS, &TRANS, &N, &N, &N, &one, EiR, &N, 
            EiR, &N, &zero, cov, &N); 

/* wrong se's:
   for(j=0;j<N;j++)
   se[j] = sqrt((*sigma)*cov[N*j+j]);
   */

}/*~~~ end reg() ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void Exit(int i, long k)
{
     printf("\n\ngn() exited with return value %d, on iteration %d",i,k+1);
}

void Free(double *a, double *b, double *c, double *d, double *e, 
          double *f,double *g, double *h)
{
     free(a);free(b);free(c);free(d);free(e);free(f);free(g);free(h);
}
