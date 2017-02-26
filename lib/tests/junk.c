#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#define MAX_NAME 100

void read_name(char *);
double dnrm2_(int *, double *, int *);/* BLAS1 L2 norm routine */

main()
{
  char *filename;
  double *x, l2norm;
  unsigned long nrow, ncol, vectrow;
  int INCX=1; /* specifies the storage spacing between successive elements */

  filename = cmalloc(MAX_NAME);

  printf("\nEnter file name containing the matrix: ");
  read_name(filename);
  printf("\nEnter the number of rows: ");
  scanf("%u",&nrow);
  printf("\nEnter the number of columns: ");
  scanf("%u",&ncol);

  x = dmalloc(nrow*ncol);
  matread(x, nrow, ncol, filename); /*matrix stored contiguously column-wise */
  matprint(x, nrow, ncol);
  vectrow = nrow-2;
  l2norm = dnrm2_(&vectrow,x+nrow+2,&INCX); /* BLAS1 L2 norm routine */
  printf("\n\nDL2 = %lf\n", l2norm);
  
}

void read_name(char *name)
{
  int c, i = 0;
  
while ((c = getchar()) != EOF && c != ' ' && c != '\n')
  name[i++] = c;
name[i] = '\0';
}

  
