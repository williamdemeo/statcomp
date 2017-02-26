/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  sweep.c

  Created on 12/16/97 by William J. De Meo
    Last modified 12/17/97

  Purpose: Perform sweep algorithm of an M dimensional symmetric matrix

           
  Further Details:  This implementation uses BLAS 1
                    Requires subroutines found in the libraries:
                    sunperf, and blas
                    the later two are linked with the options:
                    -lsunperf -dalign -lblas
                    compilation must be done with the -dalign option
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "prototypes.h"

void daxpy_(long *N, double *alpha, double *x, long *INCX, double *Y, long *INCY);
/* Y <- alpha X + Y */

/* Subroutine sweep:  perform a sweep of p columns of A

   Arguments: 
              M  (long) dimension of A

              A  (pointer to double) 
                 on entry: the M by M symmetric matrix to be swept 
                          (lower triangle is never accessed)
                 on exit: upper triangle = the swept matrix
                          (lower triangle is unchanged)

              p  (long) number of columns to be swept

              index  (pointer to long) a vector of length p containing the 
                     indices specifying which columns are to be swept
                     Note: indices can take values in [0, M-1]
*/

void sweep(long M, double *A, long p, long *index)
{
     long i;
     long k;
  
     for(i=0;i<p;i++)
     {
          k = index[i];
          colsweep(M,A,k);
      
     }
}

/* Subroutine colsweep: sweep column k of A

   Arguments: 
              M  (long) dimension of A

              A  (pointer to double) 
                 on entry: the M by M symmetric matrix to be swept 
                          (lower triangle is never accessed)
                 on exit: upper triangle = the swept matrix
                          (lower triangle is unchanged)

              k  (long) column to be swept
*/

void colsweep(long M, double *A, long k)
{

     long i,j,length,one = (long)1;
     double alpha;

     /* First convert non-k elements */

     /* rows 0 to k-1 */
     for(i=0;i<k;i++)
     {
          length = k-i;

          /* i < k, i <= j < k  (triangle) */
          /* for columns i:k of rows i:k, do the following daxpy:  */
          /* a(i,i:M) <- alpha*a(k,i:M) + a(i,i:M) */
          alpha = ((double)-1)*A[k*M+i]/A[k*M+k];
          daxpy_(&length,&alpha,A+(k*M+i),&one,A+(i*M+i),&M); 
          /* notice: replacing row k col i here ^ with row i col k since sym */

          length = M-k-1;
          /* i < k, j > k  (rectangle) */
          daxpy_(&length,&alpha,A+((k+1)*M+k),&M,A+((k+1)*M+i),&M); 

     }

     /* rows k+1 to M */
     for(i=k+1;i<M;i++)
     {
          length = M-i-1;
      
          /* k < i < j  (triangle) */
          /* for columns k:M of rows k:M, do the following daxpy:  */
          /* a(i,i:M) <- alpha*a(k,i:M) + a(i,i:M) */
          alpha = ((double)-1)*A[i*M+k]/A[k*M+k];
          daxpy_(&length,&alpha,A+(i*M+k),&M,A+(i*M+i),&M); 
     }

     /* divide elements 0:k-1 of kth col of A by a_{kk} */
     for(i=0;i<k;i++)   A[k*M+i]/=A[k*M+k];
     /* divide elements k+1:M of the kth row of A by a_{kk} */
     for(j=k+1;j<M;j++)  A[j*M+k]/=A[k*M+k];
     /* Finally, invert diagonal */
     A[k*M+k] = ((double)-1)/A[k*M+k];
}


