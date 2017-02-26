/************************************************************
 * cholesky.c  main program for testing Cholesky            *
 * decomposition routine cholesky()                         *
 *                                                          *
 * Created by William J. De Meo                             *
 * on 11/29/97                                              *
 *                                                          *
 ************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#define MAX_NAME 100

void cholesky(long N, double *A, double *diag);
void read_name(char *);

main()
{
     char *filename;
     double *A, *diag;
     long i, j, dim;
  
     filename = cmalloc(MAX_NAME);

     printf("\nEnter file name containing the spd matrix: ");
     read_name(filename);
     printf("\nEnter its dimension: ");
     scanf("%d",&dim);

     A = dmalloc(dim*dim);
     diag = dmalloc(dim);
  
     matlabread(A, dim, dim, filename); 
     /*matrix is stored contiguously column-wise */

     cholesky(dim,A,diag);
     
     printf("\nThe Cholesky factor is: \nL = \n");
     for(i=0;i<dim;i++)
     {
          for(j=0;j<i;j++)
               printf("%4.5lf \t", A[dim*j+i]);
          printf("%4.5lf", diag[i]);
          printf("\n");
     }
         
}
  
void read_name(char *name)
{
     int c, i = 0;
  
     while ((c = getchar()) != EOF && c != ' ' && c != '\n')
          name[i++] = c;
     name[i] = '\0';
}

  
