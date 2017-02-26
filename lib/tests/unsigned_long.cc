// unsigned_long.cc
// tests what happens when we pass a long to a 
// function expecting an unsigned long
#include <stdlib.h>
#include <iostream>
#include "utilities.h"
void function_expecting_an_unsigned_long(unsigned long ULong);

void function_expecting_a_long(long Long);

main()
{
  long Long, negL;
  unsigned long ULong, bigUL;
  
  Long = 100L;
  negL = -100L;
  ULong = 100UL;
  bigUL = max_long();
  bigUL += 1000000;  /* should be to large to be handled as signed long */

  cout << "Long = " << Long << endl;
  cout << "negL = " << negL << endl;
  cout << "ULong = " << ULong << endl;
  cout << "bigUL = " << bigUL << endl;

  cout << "\nTEST: passing Long to unsigned long fn: " << endl;
  function_expecting_an_unsigned_long(Long);
  cout << "TEST: passing negL to unsigned long fn: " << endl;
  function_expecting_an_unsigned_long(negL);

  cout << "\nTEST: passing ULong to long fn: " << endl;
  function_expecting_a_long(ULong);
  cout << "\nTEST: passing bigUL to long fn: " << endl;
  function_expecting_a_long(bigUL);
}

void function_expecting_an_unsigned_long(unsigned long Long)
{
  cout << "\nargument, " << endl; 
  cout << "with no type cast is: " << Long << endl;
  cout << "type cast as long is: " << (long)Long << endl;
  cout << "type cast as unsigned long is: " << (unsigned long)Long << endl;
}

void function_expecting_a_long(long Long)
{
  cout << "\nargument, " << endl; 
  cout << "with no type cast is: " << Long << endl;
  cout << "type cast as long is: " << (long)Long << endl;
  cout << "type cast as unsigned long is: " << (unsigned long)Long << endl;
}

  
