#include "unity.h"
#include "DataDecode.h"
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
  
  char *a = "01001000";
  char utf8;
	utf8 = eightBinToChar(a);
  
  TEST_ASSERT_EQUAL('H', utf8);
}

void test_binary_string_to_alphanumeric_char(void){
  
  char a = 'h';
  
  printf("%d",a);
}
