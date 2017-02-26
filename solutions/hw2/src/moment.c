/* dmoment 
   arguments:
              data = a nx1 array of doubles
              n = length of data[]
              ave =(on entry)= the address of *ave (call by reference)
              ave =(on exit)= average of data[]
              var =(on entry)= the address of *var (call by reference)
              var =(on exit)= variance of data[]
              */
void dmoment(double * data, int n, double *ave, double *var)
{
  int i;
  
  *ave=0; *var=0;
  
  for(i=0;i<n;i++){
       *ave += data[i];
       *var += data[i]^2;
  }
  *ave /= n;
  *var = (*var - n*((*ave)^2))/(n-1);
}

/* pmoment 
   arguments:
              data = a nx1 array of doubles
              n = length of data[]
              ave =(on exit)= the average of data[]
              var =(on exit)= the variance of data[]
              */
void pmoment(double * data, int n, double *ave, double *var)
{
  int k;

  *ave = data[0];
  *var=0;
  
  for(k=1;k<n;k++){
      *var += ((k-1)/k)*(data[k]-*ave)^2;
      *ave = ((k-1)/k)*(*ave) + data[k]/k;
    }
}

/* cmoment 
   arguments:
              data = a nx1 array of doubles
              ave =(on exit)= the average of data[]
              var =(on exit)= the variance of data[]
              */
void cmoment(double * data, int n, double *ave, double *var)
{
  int i;
  
  *ave=0;
  *var=0;
  for(i=1;i<n;i++){
    *ave += data[i] - data[0];
    *var += (data[i] - data[0])^2;
  }
  *ave = *ave/n + data[0];
  *var = (*var - n*((*ave)^2))/(n-1);
}

