#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"

test_passing_long_to_unsigned_long(unsigned long ULong);
main()
{
  long Long;
  unsigned long ULong;
  
  Long = 100L;
  ULong = 100UL;

  cout << "Long = " << Long << endl;
  cout << "ULong = " << ULong << endl;

  test_passing_long_to_unsigned_long(Long);
  
}

void read_name(char *name)
{
  int c, i = 0;
  
while ((c = getchar()) != EOF && c != ' ' && c != '\n')
  name[i++] = c;
name[i] = '\0';
}

  
