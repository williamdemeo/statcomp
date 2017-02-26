// test_utilities.cc
// file for testing some of the functions in utilities.cc
#include <stdlib.h>
#include <iostream>
#include "utilities.h"

int main()
{
  int np2;
  double i, eps;
  cout << "\nTesting nextpow2..." << endl;

  for(i=.5; i<10.0; i+=.25){
    np2 = nextpow2(i);
    printf("nextpow2(%1.1f) = %d\n", i, np2);
  }

  cout << "\nTesting macheps..." << endl;
  eps = macheps();
  cout << "macheps() = " << eps << endl;
  return 0;
}

  
