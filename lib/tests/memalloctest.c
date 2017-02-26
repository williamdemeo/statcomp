#include <stdlib.h>

#define M 3
#define N 2

main()
{
     double **ddmalloc(unsigned long m, unsigned long n); /* m = number rows, n = number cols */
     double *dmalloc(unsigned long n);
     double *xt;
     double **A;

     int i, j;

     A = ddmalloc((unsigned long)M,(unsigned long)N);

     for(i=0;i<M;i++)
	  for(j=0;j<N;j++)
	  {
	       printf("Enter element [%d][%d]: ",i+1,j+1);
	       scanf("%lf",&A[i][j]);
	  }

     /* Fill the array */

     /* commented */
     if(0){
	  for(i=0;i<M;i++)
	  {
	       xt=A[i];			/* set xt to the address of pointer to row i */
	       for(j=0;j<N;j++,xt+=M)		/* actually, it's row number i+1 */
	       {				/* This fills the matrix row-wise */
		    printf("Enter element [%d][%d]: ",i+1,j+1);
		    scanf("%lf",xt);
	       }
	  }
     } /* end commented */

     printf("\nThe matrix is:\nA = \n");
     
     for(i=0;i<M;i++){
	  for(j=0;j<N;j++)
	       printf("%lf  ",A[i][j]);
	  printf("\n");
     }

}
