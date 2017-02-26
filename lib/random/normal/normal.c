/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   normal.c

     Subroutine for constructing normal(0,1) random numbers 

     Arguments:
     
          u  a vector of uniform random variables

          n  the length of u

          x  on entry:  an arbitrary vector of length at least 2
             on exit:  first two elements are two normal random variables

     Return values:
     
          0  failure
             (not enough uniform random variables to construct 2 normals)

          1  success
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <math.h>


int normal(double *u, long n, double *x)
{
     static int numcount = (long)0, dencount = (long)0;
     int count = (long)0;
     double s;
     extern long I;
     dencount++;
     
     do{

       /*  The following lines display the proportion of times we are rejecting
           s, which we expect to be around .27
       if(count>0)
         {
           numcount++; 
           printf("\n\n s = %lf, prop = %lf\n\n",
                 s, (double)numcount/(double)dencount);
         }
         */
          if(I > n-2) 
               return(0);/* set external I back to 0 in main() */
          s = (2*u[I] - 1)*(2*u[I] - 1) + (2*u[I+1] - 1)*(2*u[I+1] - 1);
          I += 2;
          count++;
     }while(s >= (double)1);

     x[0] = (2*u[I] - 1)*sqrt(-2*log(s)/s); 
     x[1] = (2*u[I+1] - 1)*sqrt(-2*log(s)/s);

     return(1);

}
