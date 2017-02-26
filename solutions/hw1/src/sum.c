/*----------------------------------------------------------------------
  sum.c

  Created by William J. De Meo
    on 9/27/97

  This program adds two double precision floating point numbers.
  and was written to see what happens when such a function
  receives integer arguments.  

  The "dumb" version of the function is the default.  It expects double,
  and only double, precision floating point numbers.  If the -s option
  is specified, the "smart" version of the function is called, which gives
  the correct sum for integers, single floats, double floats, etc.
----------------------------------------------------------------------*/
#include <string.h>

main(int argc, char *argv[])	/* Possible arguments:        */
{				/* -s or s to invoke smart version */
     double sum();
     double ssum(double, double);

     int x,y,sflag=0;

     if(argv[1])
     {                               /* strcmp() returns zero if strings are equal */
	  if(!strcmp(argv[1],"-s") || !strcmp(argv[1],"s"))	
	  {
	       sflag=1;
	       printf("Argument 1: %s\nEntering Smart Mode...\n",argv[1]);
	  }
	  else printf("No valid argument passed to %s.\n",argv[0]);
     }

     printf("\nEnter first integer: "); scanf("%d",&x);
     printf("\nEnter second integer: ");scanf("%d",&y);

     if(sflag) printf("\nThe sum of %d and %d is %d.\n",x,y,(int)ssum(x,y));
     else       printf("\nThe sum of %d and %d is %d.\n",x,y,(int)sum(x,y));
}

double sum(double x, double y){ return(x+y) };
}

double ssum(double x, double y) {sum(x,y);} 
/* ssum() gets the same function definition */


































































































































