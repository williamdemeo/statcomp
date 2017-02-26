/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  prototypes.h
  Various function prototypes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
/* Prototypes for functions in utilities.c */
double *dmalloc(long N);
double **ddmalloc(long M, long N);
char *cmalloc(long N);
long *lmalloc(long N);
double dmax(double a, double b);
double dmin(double a, double b);
long umin(unsigned long a, unsigned long b);
long lmin(long a, long b);
double d3max(double a, double b, double c);
double d3min(double a, double b, double c);

/* Prototypes for functions in misc.c */
void    matread(double *x, long nrow, long ncol, char *file_to_read);
void    matlabread(double *x, long nrow, long ncol, char *file_to_read);
void    matprint(double *x, long nrow, long ncol);
void    lmatprint(long *x, long nrow, long ncol);
void    matcopy(double *from, double *to, long nrow, long ncol);
void    matwrite(double *x, long nrow, long ncol, char *file_to_write);
void    check(FILE *a);

/* Other prototypes */
void qr(long nrow, long ncol, double *A, double *leadu);
void qrpivot(long M, long N, double *A, double *P, double *leadu);
void House(long N, double *a, double *u);
void cholesky(long N, double *A, double *diag);
void dmoment(double *data, long n, double *ave, double *var);
void pmoment(double *data, long n, double *ave, double *var);
void cmoment(double *data, long n, double *ave, double *var);
void colsweep(long M, double *A, long k);
void sweep(long M, double *A, long p, long *index);

/* Prototypes for random numbers */
int normal(double *u, long n, double *X);
double unif(long *X);


