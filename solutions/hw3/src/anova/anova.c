/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  anova.c

  Created by William J. De Meo
  on 11/30/97

  Purpose: Simulating F-statistics for one way ANOVA
           using correlated and uncorrelated data

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <math.h>
#include <stdio.h>
#include "prototypes.h"

/* NAG prototypes */
double g01fdf_(double *p, double *DF1, double *DF2, int *ifail);
void m01caf_(double *RV, long *M1, long *M2, char *ORDER, int *ifail);
void g05fdf_(double *mean,double *sd,long *n,double *g);

/* BLAS prototypes */
/* C <- (alpha)AB + (beta)C   */
void dgemm_(char *TRANSA, char *TRANSB, long *M, long *N, long *K, double *alpha, 
            double *A, long *LDA, double *B, long *LDB, double *beta, double *C,long *LDC); 

void  F(long N, long *n, long k, double *AVE, double *ave, double *var, double *eff);

extern long I = (long)0;

main()
{
     char ORDER = 'A';  /* F stats will be sorted in ascending order */
     int ifail = 0;
     long k, i,j,p,q,r, N=(long)0, M = (long)12, numF,f, one = (long)1;
     double *eff, *pureff, *u, *g, *gtemp, *AVE, *VAR,*ave, *var, *sig, *diag, *work;
     double minimum=(double)1000, maximum=(double)-1000,P1,P2,P3,unit=(double)1,zero=(double)0;
     long *X, *n;

     /* BLAS arguments */
     double alpha = (double)1, beta = (double)0;
     char NOTRANS = 'N';

     AVE = dmalloc((long)1);
     VAR = dmalloc((long)1);
     gtemp = dmalloc((long)2);
     X = lmalloc((long)1);
     *X = time('\0');

     printf("\nHow many groups? ");
     scanf("%d",&k);
     
     n = lmalloc(k); /* n vector stores number in each group */
     ave = dmalloc(k);
     var = dmalloc(k);

     for(i=0;i<k;i++)
     {
          printf("\nHow many in group %d? ", i+1);
          scanf("%d",n+i);
          N+=n[i];
     }
     M = 2*N;  /* unifs fail about 27% of the time, so take twice as many */
     g = dmalloc(N+1); /* normals will be stored in g (N+1 in case N odd)*/
     u = dmalloc(M);   

     printf("\nHow many simulated F's for this group structure? ");
     scanf("%d",&numF);
     eff = dmalloc(3*numF);  /* matrix of F-stats with df's */
     pureff = dmalloc(numF); /* vector of F-stats (without df's) */

     for(f=0;f<numF;f++)
     {

          I = (long)0;
          for(r=0;r<M;r++)
               u[r] = unif(X);

          i=(long)0; 
          p=(long)0;

          for(j=0;j<k;j++)
          {
               /*Forced to scrap the following broken random number generating code */
               /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/              
               if(0) 
               {
                    while(i<n[j])            
                    {           
                         if(normal(u, M, gtemp)==1)
                         {
                              g[p+i] = gtemp[0];  i++;
                              g[p+i] = gtemp[1];  i++;
                         }
                         else  /* didn't get enough normals -- need new uniforms */
                         {                    
                              printf("\n\nGenerating different unif(0,1) variables...\n\n");
                              I = 0;
                              for(r=0;r<M;r++)
                                   u[r] = unif(X);
                         }
                    }
                    if(i==n[j])/* i.e. even number in group */
                         i=(long)0;
                    else i=(long)1; /* i.e. odd number in group */
                    /*then give last random number to the next group */
               }
               /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

               /* NAG routine puts  normal(0,1) random numbers in g */
               g05fdf_(&zero,&unit,n+j,g+p);

               /* compute group averages and variances */
               cmoment(g+p, n[j], ave+j, var+j);  
               /*printf("\nave[%d] = %lf, var[%d] = %lf\n\n",j+1,ave[j],j+1,var[j]);*/
               
               p+=n[j];
          }

          cmoment(g,N,AVE,VAR);  /* Get overall average */

          /* finally compute the associated F-statistic */
          F(N,n,k,AVE,ave,var,eff+3*f);
     }

     /* strip degrees of freedom from eff (so we can sort it) */
     for(j=0;j<numF;j++)
          pureff[j] = eff[j*3];

     /* sort the pureff vector of F statistics */
     m01caf_(pureff, &one, &numF, &ORDER, &ifail);     
     printf("\n\nUNCORRELATED DATA\n");
     printf("-------------------\n");
     P1 = (double).9;
     P1 = g01fdf_(&P1,eff+1,eff+2,&ifail);
     printf("\n90th percetile: theoretical = %lf, observed = %lf\n",P1,pureff[(long)(.9*numF)]);
     P2 = (double).95;
     P2 = g01fdf_(&P2,eff+1,eff+2,&ifail);
     printf("\n95th percetile: theoretical = %lf, observed = %lf\n",P2,pureff[(long)(.95*numF)]);
     P3 = (double).99;
     P3 = g01fdf_(&P3,eff+1,eff+2,&ifail);
     printf("\n99th percetile: theoretical = %lf, observed = %lf\n",P3,pureff[(long)(.99*numF)]);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Correlated data
  WARNING:  This part only written for non-ragged arrays
  i.e. all k group sizes must be equal*/

/* Test to see that all group sizes equal */
     for(j=0;j<k;j++)
          if(n[0]!=n[j])
          {
               printf("\n\nGroups of different sizes\n");
               printf("\n Can't perform correlation simulations.\n");
               exit(0);
          }

     /* now just refer to group size as *n */
     
     sig = dmalloc(*n * *n);
     diag = dmalloc(*n);
     work = dmalloc(N);

     for(f=0;f<numF;f++)
     {
          /* NAG routine puts  normal(0,1) random numbers in g */
          g05fdf_(&zero,&unit,&N,g);

          for(j=0;j<*n;j++) 
               for(i=j;i<*n;i++) /* only need lower triangle of symmetric matrix */
                    sig[*n *j+i]=pow(0.7,(i-j));
          for(i=0;i<*n;i++)
               for(j=i+1;j<*n;j++) 
                    sig[*n * j +i]=0;

          cholesky(*n, sig, diag);
          for(j=0;j<*n;j++) sig[*n * j +j]=diag[j]; 
          free(diag);

          /*work <- sig*g */
          dgemm_(&NOTRANS, &NOTRANS, n, &k,n, &alpha, sig, n, g, n, &beta, work, n);      
          for(j=0;j<N;j++) g[j] = work[j];
          
          /* compute group averages and variances */
          p=(long)0;
          for(j=0;j<k;j++)
          {
               cmoment(g+p, n[j], ave+j, var+j);  
               p+=n[j];
          }
          /*printf("\nave[%d] = %lf, var[%d] = %lf\n\n",j+1,ave[j],j+1,var[j]);*/
               
          cmoment(g,N,AVE,VAR);  /* Get overall average */

          /* finally compute the associated F-statistic */
          F(N,n,k,AVE,ave,var,eff+3*f);
     }
     
     /* strip degrees of freedom from eff (so we can sort it) */
     for(j=0;j<numF;j++)
          pureff[j] = eff[j*3];

     /* sort the pureff vector of F statistics */
     m01caf_(pureff, &one, &numF, &ORDER, &ifail);     
     printf("\n\nCORRELATED DATA\n");
     printf("-------------------\n");
     printf("\n90th percetile: theoretical = %lf, observed = %lf\n",P1,pureff[(long)(.9*numF)]);
     printf("\n95th percetile: theoretical = %lf, observed = %lf\n",P2,pureff[(long)(.95*numF)]);
     printf("\n99th percetile: theoretical = %lf, observed = %lf\n",P3,pureff[(long)(.99*numF)]);

}

/* subroutine F() ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   
   Purpose:  Compute test statistic for equality of means

   Arguments:
   
             N  total number of observations

             n  a vector of length k where the ith element
                contains the number of observations in the ith group
             
             k  the number of groups

             AVE  average of all observations

             ave  a vector of length k where the ith element
                  contains the average of the ith group of observations

             var  a vector of length k where the ith element
                  contains the empirical variance (mse) of the ith group of observations

             F  on entry: a vector of length 3
                on exit: first element is the F-statistic
                         second element is k-1, third element is N-k
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
             
void  F(long N, long *n, long k, double *AVE, double *ave, double *var, double *F)
{
     long i,j;
     double den=(double)0,num=(double)0;
     
     F[1]=k-1; F[2]=N-k;
     
     for(i=0;i<k;i++)
     {
          num += n[i]*(ave[i]-*AVE)*(ave[i]-*AVE)/F[1];
          den += (n[i]-1)*var[i]/F[2];
     }
     
     F[0] = num/den;
               
}

