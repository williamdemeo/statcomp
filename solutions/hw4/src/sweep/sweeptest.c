/************************************************************
 * sweeptest.c  main program for testing sweep subroutine   *
 *                                                          *
 * Created by William J. De Meo                             *
 * on 12/17/97                                              *
 *                                                          *
 ************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#define MAX_NAME 100

void read_name(char *);

main()
{
     char *filename;
     double *x;
     long i, k, nrow, *index;

     filename = cmalloc(MAX_NAME);

     printf("\nEnter name of the file containing the symmetric matrix: ");
     read_name(filename);
     printf("\nEnter the dimension: ");
     scanf("%u",&nrow);
     
     printf("\nEnter number of columns to be swept: ");
     scanf("%u",&k);
     index = lmalloc(k);

     for(i=0;i<k;i++)
     {
          printf("\ncolumn for sweep %d: ",i);
          scanf("%u",index+i);
     }

     x = dmalloc(nrow*nrow);
     /* matread(x, nrow, ncol, filename);  */
     matlabread(x, nrow, nrow, filename); 
     /*matrix is stored contiguously column-wise */
     printf("\nThe matrix is: \n");
     matprint(x,nrow,nrow);
     
     /* Test sweep: */
     sweep(nrow,x,k,index);               

     printf("\nThe sweep produced: \n");
     matprint(x,nrow,nrow);
}
  
void read_name(char *name)
{
     int c, i = 0;
  
     while ((c = getchar()) != EOF && c != ' ' && c != '\n')
          name[i++] = c;
     name[i] = '\0';
}

  
