/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  random.c

  Purpose: main program for testing routine normal()
           for generating normal(0,1) random variables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <math.h>
#include <stdio.h>
#include "prototypes.h"

double max(double a, double b, double c);
double min(double a, double b, double c);

main()
{
     long n, m, i,j;
     double *u, *g, *gtemp, *ave, *var, minimum = 100, maximum = -100;
     long *X;
     FILE *ofp;

     ave = dmalloc((long)1);
     var = dmalloc((long)1);
     gtemp = dmalloc((long)2);
     X = lmalloc((long)1);
     *X = time('\0');

     printf("\nHow many normal random variables? ");
     scanf("%d",&m);
     n = 2*m; /* generate two times as many uniforms */

     ofp = fopen("norm.out", "a");

     u = dmalloc(n);
     for(i=0;i<n;i++)
          u[i] = unif(X);

     cmoment(u, n, ave, var);
     fprintf(ofp,"\n\nUAverage = %lf, UVariance = %lf\n",*ave,*var);

     fprintf(ofp,"\nThe normal(0,1) random variables are:\n\n");
     g = dmalloc(m);
     for(i=0;i<m;i++)
     {
          if(normal(u, n, gtemp)==1)
          {
               g[i] = gtemp[0]; 
               g[++i] = gtemp[1];
               maximum = max(maximum,g[i-1], g[i]);
               minimum = min(minimum,g[i-1], g[i]);
               fprintf(ofp,"%lf  %lf  ",g[i-1], g[i]); 
               if((i+1)%6 == 0) fprintf(ofp,"\n"); 
          }
          else  /* didn't get enough normals -- need new uniforms */
          {
               i = 0;
               printf("\n\nGenerating different unif(0,1) variables...\n\n");
               for(j=0;j<n;j++)
                    u[j] = unif(X);
          }
     }
     cmoment(g, m, ave, var);
     fprintf(ofp,"\n\nAverage = %lf, Variance = %lf, min = %lf, max = %lf \n"
             ,*ave,*var, minimum, maximum);
     fclose(ofp);
}

double max(double a, double b, double c)
{
     double max;
     if(a >= b) max = a;
     else max = b;

     if(max >= c) return(max);
     else return(c);
}

double min(double a, double b, double c)
{
     double min;
     if(a <= b) min = a;
     else min = b;

     if(min <= c) return(min);
     else return(c);
}
