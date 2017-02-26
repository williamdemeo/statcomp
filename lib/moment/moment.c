
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   moment.c
  
   Three routines for for computing the mean and variance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* dmoment: The desk calculator algorithm
   arguments:
              data = a nx1 array of doubles
              n = length of data[]
              ave =(on entry)= the address of *ave (call by reference)
              ave =(on exit)= average of data[]
              var =(on entry)= the address of *var (call by reference)
              var =(on exit)= variance of data[]
              */
void dmoment(double * data, long n, double *ave, double *var)
{
     long i;
  
     *ave=0; *var=0;
  
     for(i=0;i<n;i++){
          *ave += data[i];
          *var += data[i]*data[i];
     }
     *ave /= (double) n;
     *var = (*var - (double)n*((*ave)*(*ave)))/(double)(n-1);
}

/* pmoment: The provisional means algorithm
   arguments:
              data = a nx1 array of doubles
              n = length of data[]
              ave =(on exit)= the average of data[]
              var =(on exit)= the variance of data[]
              */
void pmoment(double * data, long n, double *ave, double *var)
{
     long i;

     *ave = data[0];
     *var=0;
  
     for(i=1;i<n;i++){
          *var +=((double)i/(double)(i+1))*(data[i]-*ave)*(data[i]-*ave);
          *ave *= ((double)i/(double)(i+1));
          *ave += data[i]/(double)(i+1);
     }
     *var /= (double)(n-1);
}

/* cmoment: centering around the first observation 
   arguments:
              data = a nx1 array of doubles
              ave =(on exit)= the average of data[]
              var =(on exit)= the variance of data[]
              */
void cmoment(double * data, long n, double *ave, double *var)
{
     long i;
  
     *ave=0;
     *var=0;
     for(i=1;i<n;i++){
          *ave += data[i] - data[0];
          *var += (data[i] - data[0])*(data[i] - data[0]);
     }
     *ave /= (double)n;
     *var = (*var - (double)n * ((*ave)*(*ave)))/(double)(n-1);
     *ave += data[0];
}


