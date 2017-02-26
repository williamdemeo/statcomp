#include <stdio.h>
#include <stdlib.h>
#include </accounts/grad/chip/classes/lib/prototypes.h>

main(int argc, char **argv)
{
       double *dave, *dvar, *pave, *pvar, *cave, *var, *x;
     FILE *ifp, *ofp;
     int i;
     
     if(argc != 3)
{
  prn_info(argv[0]);
  exit(1);
}
     ifp = fopen(argv[1], "r");
     ofp = fopen(argv[2], "w");
x = dmalloc(54);
x = readdata(ifp, 54, 0);

printf("\nx = \n");

for(i=0; i<54; i++) printf(" %lf ",*x++);

}



