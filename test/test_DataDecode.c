#include "unity.h"
#include "DataDecode.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_binary_string_to_UTF8(void){
  
  char *a;
  
  int b[] = {0,1,0,0,1,0,0,0};
  int bb = 0, i;
  
  a = utf8Conversion(b);
  
  // printf("%s", a);
  // TEST_ASSERT_EQUAL("H", a);
}

void test_getMode(void){
  
  Mode mode;
  int arr[] = {0,1,0,0};
  mode = getMode(arr);
  
  TEST_ASSERT_EQUAL(2, (int)mode);
}
