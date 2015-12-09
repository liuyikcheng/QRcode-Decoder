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
  
  int b[] = {0,1,1,0,0,1,0,1};
  int bb = 0, i;
  
  a = utf8Conversion(b, 0);
  
  // TEST_ASSERT_EQUAL_PTR("H", a);
}

void test_getMode_should_return_BYTE(void){
  
  Mode mode;
  int arr[] = {0,1,0,0};
  mode = getMode(arr);
  
  TEST_ASSERT_EQUAL(BYTE, mode);
}

void test_QrBitReaderInfo_with_Byte_mode_and_Hello_message_data(void){
  int data[] = {0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1};
  QrBitReaderInfo *qrBitReaderInfo = malloc(sizeof(QrBitReaderInfo));
  dataDecode((int*)data, qrBitReaderInfo);
  
 printf("%s", qrBitReaderInfo->strData);
}