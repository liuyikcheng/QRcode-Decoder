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

void test_binary_string_1101100011_to_three_numeric_characters_867(void){
  char *str;
  int data[] = {1,1,0,1,1,0,0,0,1,1};
  
  str = numericConversion(data, 0, 3);
  
  TEST_ASSERT_EQUAL(0, strcmp("867",str));
}

void test_binary_string_1001001_to_two_numeric_characters_73(void){
  char *str;
  int data[] = {1,0,0,1,0,0,1};
  
  str = numericConversion(data, 0, 2);
  
  TEST_ASSERT_EQUAL(0, strcmp("73",str));
}

void test_binary_string_0101_to_one_numeric_character_5(void){
  char *str;
  int data[] = {0,1,0,1};
  
  str = numericConversion(data, 0, 1);
  
  TEST_ASSERT_EQUAL(0, strcmp("5",str));
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

void test_getNumOfCountBit_with_version_1_and_alphanumeric_mode_should_return_9(void){
  
  int countBit;
  countBit = getNumOfCountBit(ALPHANUMERIC, 1);
  
  TEST_ASSERT_EQUAL(9, countBit);
}

void test_getNumOfCountBit_with_version_10_and_BYTE_mode_should_return_16(void){
  
  int countBit;
  countBit = getNumOfCountBit(BYTE, 10);
  
  TEST_ASSERT_EQUAL(16, countBit);
}

void test_getNumOfCountBit_with_version_35_and_NUMERIC_mode_should_return_14(void){
  
  int countBit;
  countBit = getNumOfCountBit(NUMERIC, 35);
  
  TEST_ASSERT_EQUAL(14, countBit);
}

void test_getCharCap_with_version_4_and_NUMERIC_mode_and_errLevel_M_should_return_149(void){
  
  int charCap;
  charCap = getCharCap(NUMERIC, 4, M);
  
  TEST_ASSERT_EQUAL(149, charCap);
}

void test_getCharCap_with_version_5_and_BYTE_mode_and_errLevel_Q_should_return_60(void){
  
  int charCap;
  charCap = getCharCap(BYTE, 5, Q);
  
  TEST_ASSERT_EQUAL(60, charCap);
}

void test_getCharCap_with_version_18_and_ALPHANUMERIC_mode_and_errLevel_L_should_return_1046(void){
  
  int charCap;
  charCap = getCharCap(ALPHANUMERIC, 18, L);
  
  TEST_ASSERT_EQUAL(1046, charCap);
}

void test_QrBitReaderInfo_with_version1_Byte_mode_and_Hello_message_data(void){
  int data[] = {0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1};
  char *message;
  
  message = msgDecode((int*)data, BYTE, 0, 8, 1);
    
  TEST_ASSERT_EQUAL(0, strcmp("Hello",message));

}

void test_QrBitReaderInfo_with_Byte_mode_and_Hello_message_data(void){
  int data[] = {0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,1};
  char *message;
  QrBitReaderInfo* qrBitReaderInfo = malloc(sizeof(QrBitReaderInfo));
  message = dataDecode((int*)data, qrBitReaderInfo);
    
  TEST_ASSERT_EQUAL(0, strcmp("Hello",message));

}

void test_QrBitReaderInfo_with_Alphanumeric_mode_and_Hello_world_message_data(void){
  int data[] = {0,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,0,0,0,1,0,1,1,0,1,1,1,1,0,0,0,1,1,0,
                1,0,0,0,1,0,1,1,1,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0,1,1,0,1,
                1,1,1,1,1};
                
  char *message;

  message = dataDecodeMsg((int*)data, 1, L);
  
  // printf("%s", message);
  
  TEST_ASSERT_EQUAL(0, strcmp("HELLO WORLD",message));

}

void test_QrBitReaderInfo_with_numeric_mode_and_8675309_message_data(void){
  int data[] = {0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,1,0,0,1};
  char *message;
  
  message = dataDecodeMsg((int*)data, 1, L);

  
  TEST_ASSERT_EQUAL(0, strcmp("8675309",message));

}