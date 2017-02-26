/************************************************************
 * QRtime.c  main program for timing the QR                 *
 * Orthogonalization routine qr()                           *
 *                                                          * 
 * Created by William J. De Meo                             *
 * on 2001.11.01                                            *
 ************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "prototypes.h"
#include "timer.h"
#define MAX_NAME 100

void qr(long M, long N, double *A, double *leadu);  
void read_name(char *);

main()
{
  /*     char *filename;*/
  char filename[] = "datafile";
  double *x, *leadu, *P;
  long i, j, nrow, ncol, mindim;
  /*     filename = cmalloc(MAX_NAME);*/

  nrow = 100;
  ncol = 100;

  /*     printf("\nEnter file name containing the matrix: ");
     read_name(filename);
     printf("\nEnter the number of rows: ");
     scanf("%u",&nrow);
     printf("\nEnter the number of columns: ");
     scanf("%u",&ncol);
  */
     mindim = lmin(nrow,ncol); /* mindim is the smaller dimension */

     x = dmalloc(nrow*ncol);
     leadu = dmalloc(mindim);
     P = dmalloc(ncol*ncol);
  
     matlabread(x, nrow, ncol, filename); 
     /*matrix stored contiguously column-wise */

     TIME0  /* timing qr routine */
     /* Test qr():  */
     qr(nrow,ncol,x,leadu);
     TIME1("time for C qr deomposition (no-pivot)");

     if(0){
       printf("\nThe orthogonalization produced: \n");
       matprint(x,nrow,ncol);
       printf("\nwith leading u's:\n");
       for(i=0;i<mindim;i++)
	 printf("%4.5lf \t", leadu[i]);
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

  
