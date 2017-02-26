
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   illtest.c

   purpose:  Test the routines dmoment, pmoment, cmoment in 
             file moment.c on illconditioned data .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prototypes.h"

#define small 0.0000001
#define BIG 10

main()
{
     double  *relerr, *dave, *dvar, *pave, *pvar, *cave, *cvar, *x;
     double VAR, coef;
     unsigned long i=0,n, count=0;
     int flag=0, j;
     FILE *ofp;       
  
     dave = dmalloc(1);
     dvar = dmalloc(1);
     pave = dmalloc(1);
     pvar = dmalloc(1);
     cave = dmalloc(1);
     cvar = dmalloc(1);
  
     printf("\nHow many data values? ");
     scanf("%d",&n);
     x = dmalloc(n);

     printf("\nEnter data values at the > prompt. ");
     for(i=0;i<n;i++){
          printf("\n> ");
          scanf("%lf",&x[i]);
     }
     dmoment(x, n, dave, dvar);
     pmoment(x, n, pave, pvar);
     cmoment(x, n, cave, cvar);

     ofp = fopen("illout", "w");
     fprintf(ofp,"\nx = \n");
     for(i=0; i<n; i++) fprintf(ofp," %lf ",x[i]);
     fprintf(ofp,"\n\n(dave,dvar) = (%lf,%lf)",*dave,*dvar);
     fprintf(ofp,"\n\n(pave,pvar) = (%lf,%lf)",*pave,*pvar);
     fprintf(ofp,"\n\n(cave,cvar) = (%lf,%lf)\n",*cave,*cvar);

     /* Ill-conditioning */

     VAR = *dvar; /* the "true" mean and variance */
     relerr = dmalloc(3);

     while(flag<2) 
     {
          count++;          
          for(i=0;i<n;i++) x[i]+=pow(2,count); 

          dmoment(x, n, dave, dvar);
          pmoment(x, n, pave, pvar);
          cmoment(x, n, cave, cvar);

          relerr[0] = (*dvar - VAR)/VAR;
          relerr[1] = (*pvar - VAR)/VAR;
          relerr[2] = (*cvar - VAR)/VAR;
          coef = sqrt(VAR)/(*pave);
                        
          /* If any relative errors are bigger than small, */
          /* print a warning.  If any are bigger than BIG, exit. */
          for(j=0;j<3;j++) {
               if(relerr[j] > small || -relerr[j] > small) 
                  fprintf(ofp,
                    "\nWarning: on iteration %u, relerr[%d] = %g, coef = %g",
                    count,j,relerr[j],coef);
               if(relerr[j] > BIG || -relerr[j] > BIG) {
                  fprintf(ofp,
                    "\nERROR:   on iteration %u, relerr[%d] = %g, coef = %g",
                    count, j,relerr[j],coef);
                  flag++;
               }
          }
     }
     fprintf(ofp,"\n\n%s%u%s%s%lf %s%lf %s%lf %s%lf\n ",
             "On iteration ", count,
             " at least two gross errors:\n",
             "VAR = ", VAR,
             "\ndvar = ", *dvar, 
             "\npvar = ", *pvar, 
             "\ncvar = ", *cvar);
     fclose(ofp);
}
