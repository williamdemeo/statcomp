/*----------------------------------------------------------------------
  chisquare.c

  Created by William J. De Meo
    on 10/7/97

    Purpose:  This program obtains degrees of freedom (df) and 
    left tail probability level (p) from the user, 
    generates the corresponding Chi-square value, and awaits another query.

    Notes: On the SCF network, type xnaghelp for documentation regarding 
           the NAG subroutine g01fcf_
----------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

void main()
{
     double df,p,chi;
     char another='y';
     int ifail;			/* -1 instructs routine to */
     /* report errors and continue */

     double g01fcf_(double *p, double *df, int *ifail);

     while(((another!='x') && (another!='X')) || another=='\0')
     {
	  printf("\nEnter the left tail probability level: "); scanf("%lf",&p);
	  printf("\nEnter the degrees of freedom: "); scanf("%lf",&df);

	  ifail = -1;
	  chi = g01fcf_(&p,&df,&ifail);

	  if(ifail != 0)
	  {
	       switch(ifail){
	       case 1:
		    printf("\nProbability level out of range [0,1).");
		    break;
	       case 2:
		    printf("\nDegrees of freedom not greater than 0.");
		    break;
	       case 3:
		    printf("\nProbability too close to 0 or 1 for \
value to be calculated.");
		    break;
	       case 4:
		    printf("\nSolution failed to converge. \
Result is only an approximation.");
		    printf("\nThe corresponding chi-square value is: %lf\n", chi);
		    printf("\nThat is, P( Chi-square_(%lf) < %lf ) = %lf", df,chi,p);

		    break;
	       case 5:
		    printf("\nSolution failed to converge.");
		    break;
	       default:
		    break;
	       }
	  }
	  else
	  {
	       printf("\nThe corresponding chi-square value is: %lf\n", chi);
	       printf("\nThat is, P( Chi-square_(%d) < %lf ) = %lf", (int)df,chi,p);
	  }
	  printf("\n\nPress X to exit, or any other character to continue: ");
	  scanf("%1s",&another);
     }
}
