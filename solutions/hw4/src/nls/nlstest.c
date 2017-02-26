/***********************************************************************
  nlstest.c  main program for testing gn() subroutine     
                                                          
  Created by William J. De Meo on 12/20/97 
       last modified on 12/21/97
            
  Purpose:  Perform non-linear least squares using the gn() 
            implementation of the Gauss Newton algorithm found in 
            /accounts/grad/chip/lib/gauss/gn.c
            The following desribes the problem used for the test:

            (Source: BMDP manual, p. 395)

            An experiment was carried out wherein varying doses of 
            Rose Bengal, an enzyme, was used as a catalyst for the 
            production of an protein substrate.  The concentration
            of the substrate was measured spectrophotometrically.
            The first column of the data represents the dose of the 
            enzyme, and the second column the spectrophotometric 
            response.  The equation proposed for the data is
            
            
                              v * dose
            response  =     ------------ , 
                             (k + dose)
           
            where v and k are the parameters to estimated.  (This equation
            is known as the Michaelis-Menten model for the velocity of an
            enzyme catalyzed reaction.)

            The data are:

            dose   response
            0.027  12.7
            0.044  16.0
            0.073  20.4
            0.102  22.3
            0.175  26.0
            0.257  28.8
            0.483  29.6
            0.670  31.4
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "prototypes.h"
#define MAX_NAME 100

/* Data specific settings: */
/* number of observations */
#define M 8
/* number of covariates */
#define N 1
/* number of parameters */
#define P 2

#define MAXITER 20

void init(double *);
void eta(long, long, double *, long , double *, double *);
void jac(long, long, double *, long , double *, double *);
void (*f)(long, long, double *, long , double *, double *);
void (*g)(long, long, double *, long , double *, double *);

void gn(long , long, double *X, double *Y, long, double *theta,
        void   (*f)(long , long , double *X, long , double *theta, double *F), 
        void   (*g)(long , long , double *X, long , double *theta, double *J),
        double *cov, double *sigma, long iter);

void read_name(char *name);

main()
{
     double *x, *y, *theta, *cov, *sigma, *se;
     long i, j;
     char *filename;
     
     filename = cmalloc(MAX_NAME);
     printf("\nEnter file name containing the data: ");
     read_name(filename);

     x = dmalloc(M*(N+1));
     y = x+M; /* y is assigned the address of second col of x */
     theta = dmalloc(P);
     se = dmalloc(P);
     cov = dmalloc(P*P);
     sigma = dmalloc((long)1);

     matread(x, M, N+1, filename); 

     init(theta);

     f = eta;
     g = jac;
     
     gn(M,N,x,y,P,theta,f,g,cov,sigma,MAXITER);

     /* compute se's:  */
     for(j=0;j<P;j++)
          se[j] = sqrt((*sigma)*cov[P*j+j]);        
     printf("\n\nMSE = %lf\n",*sigma);
     printf("\nCOEFFICIENT \t SE \n");
     for (i = 0; i < P; i++)
          printf("%4.5lf \t %4.5lf\n", theta[i],se[i]);
}

void init(double *theta)
{
     theta[0]=(double)30;
     theta[1]=(double)0.065;
}

void eta(long m, long n, double *x, long p, double *th, double *F)
{
     long i;
     for(i=0;i<m;i++)
          F[i] = (th[0] * x[i])/(th[1] + x[i]);
}

void jac(long m, long n, double *x, long p, double *th, double *J)
{
     long i;
  
     for(i=0;i<m;i++)
     {
          J[i] = x[i]/(th[1] + x[i]);
          J[M+i] = -th[0]*x[i]/pow((th[1] + x[i]),2);
     }
}

void read_name(char *name)
{
     int c, i = 0;
  
     while ((c = getchar()) != EOF && c != ' ' && c != '\n')
          name[i++] = c;
     name[i] = '\0';
}

  
