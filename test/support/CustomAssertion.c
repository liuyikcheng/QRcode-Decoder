#include "CustomAssertion.h"

void customTestAssertArray(int *expected, int *current, int numOfElem, int lineNo){
  int i;
  
  for (i = 0; i < numOfElem; i++)
    if (expected[i] != current[i])
     CUSTOM_TEST_FAIL(lineNo, "Expect %d but received %d in %d element", expected[i], current[i], i);
  
}