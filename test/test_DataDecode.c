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

void test_binary_string_01100101_to_UTF8_e(void){
  
  char *str;
  int data[] = {0,1,1,0,0,1,0,1};
  
  str = utf8Conversion(data, 0);
  
  TEST_ASSERT_EQUAL(0, strcmp("e",str));
}

void test_binary_string_1101100011_to_one_numeric_character_867(void){
  char *str;
  int data[] = {1,1,0,1,1,0,0,0,1,1};
  
  str = numericConversion(data, 0, 3);
  
  TEST_ASSERT_EQUAL(0, strcmp("867",str));
}

void test_binary_string_001101_to_one_alphanumeric_character_D(void){
  
  char *str;
  int data[] = {0,0,1,1,0,1};
  
  str = alpnumConversion(data, 0, 0);
  TEST_ASSERT_EQUAL(0, strcmp("D",str));
}

void test_binary_string_01100001011_to_two_alphanumeric_character_HE(void){
  
  char *str;
  int data[] = {0,1,1,0,0,0,0,1,0,1,1};
  
  str = alpnumConversion(data, 0, 1);
  
  TEST_ASSERT_EQUAL(0, strcmp("HE",str));
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
    
  TEST_ASSERT_EQUAL(0, strcmp("Hello",qrBitReaderInfo->strData));

}

void test_QrBitReaderInfo_with_Alphanumeric_mode_and_Hello_world_message_data(void){
  int data[] = {0,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,0,0,1,1,0,
                1,0,0,0,1,0,1,1,1,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,1,
                1,1,1,1,1};
  QrBitReaderInfo *qrBitReaderInfo = malloc(sizeof(QrBitReaderInfo));
  dataDecode((int*)data, qrBitReaderInfo);
  
  // printf("%s", qrBitReaderInfo->strData);
  
  TEST_ASSERT_EQUAL(0, strcmp("HELLO WORLD",qrBitReaderInfo->strData));

}