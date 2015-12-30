#include "unity.h"
#include "QRcodeDecode.h"
#include "ZigZagReading.h"
#include "patternFilter.h"
#include "QrMask.h"
#include "DataDecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define B   1
#define w   0

#define get_Width(x)    sqrt(sizeof(x)/4)

void setUp(void)
{
}

void tearDown(void)
{
}

//QR code contains message "ABC 123456789" Byte mode, error correction level is Low
void test_version_1_qrcode_return_message_ABC_123456789(void){
  int qrCode [21] [21]  =    {{B,B,B,B,B,B,B,w,w,B,w,B,B,w,B,B,B,B,B,B,B},
                              {B,w,w,w,w,w,B,w,B,B,w,B,w,w,B,w,w,w,w,w,B},
                              {B,w,B,B,B,w,B,w,B,B,w,w,B,w,B,w,B,B,B,w,B},
                              {B,w,B,B,B,w,B,w,w,B,w,B,w,w,B,w,B,B,B,w,B},
                              {B,w,B,B,B,w,B,w,B,w,w,w,B,w,B,w,B,B,B,w,B},
                              {B,w,w,w,w,w,B,w,B,w,w,B,B,w,B,w,w,w,w,w,B},
                              {B,B,B,B,B,B,B,w,B,w,B,w,B,w,B,B,B,B,B,B,B},
                              {w,w,w,w,w,w,w,w,B,B,B,B,B,w,w,w,w,w,w,w,w},
                              {B,B,w,B,w,w,B,B,w,B,B,w,w,w,B,B,B,w,B,B,w},
                              {w,w,w,B,B,w,w,w,w,B,w,B,w,w,w,w,B,B,w,B,w},
                              {B,w,B,B,w,w,B,B,w,w,w,w,B,B,B,w,w,w,w,w,B},
                              {B,B,B,B,w,B,w,w,B,B,w,B,w,B,B,w,B,B,w,w,B},
                              {w,B,B,B,B,B,B,B,w,w,B,w,w,B,w,w,B,w,B,w,B},
                              {w,w,w,w,w,w,w,w,B,B,B,w,B,B,w,w,w,B,w,w,w},
                              {B,B,B,B,B,B,B,w,B,w,B,B,B,B,w,w,B,w,w,B,w},
                              {B,w,w,w,w,w,B,w,w,w,w,B,w,B,w,B,B,B,w,w,w},
                              {B,w,B,B,B,w,B,w,w,B,B,w,w,w,w,w,w,w,w,w,w},
                              {B,w,B,B,B,w,B,w,B,B,B,B,B,w,B,w,B,w,w,B,B},
                              {B,w,B,B,B,w,B,w,w,B,w,w,B,w,w,w,B,w,B,w,B},
                              {B,w,w,w,w,w,B,w,B,w,w,w,B,w,w,w,B,B,w,w,w},
                              {B,B,B,B,B,B,B,w,B,w,w,w,B,B,B,w,B,w,w,B,w}
                            };
  
  QrMatrix *qrMatrix;
  qrMatrix = decodeQr((int*)qrCode, get_Width(qrCode));
  // printf("%s",qrMatrix->msg);
  TEST_ASSERT_EQUAL(0, strcmp("ABC 123456789", qrMatrix->msg));
  TEST_ASSERT_EQUAL(1, qrMatrix->qrBitReaderInfo->version);
  TEST_ASSERT_EQUAL(7, qrMatrix->qrBitReaderInfo->format->maskType);
  TEST_ASSERT_EQUAL(LOW, qrMatrix->qrBitReaderInfo->format->eccLevel);
}

//Create a qr code 2d array matrix version 2
void test_version_2_qrcode_return_message_pi_equal_3_dot_14159265358979(void)
{
	int qrCode [25] [25] =  {{B,B,B,B,B,B,B,w,w,w,B,w,B,w,B,w,w,w,B,B,B,B,B,B,B},
                            {B,w,w,w,w,w,B,w,B,w,B,w,w,B,B,B,B,w,B,w,w,w,w,w,B},
                            {B,w,B,B,B,w,B,w,w,w,w,w,B,w,B,B,w,w,B,w,B,B,B,w,B},
                            {B,w,B,B,B,w,B,w,B,B,B,w,B,B,w,w,B,w,B,w,B,B,B,w,B},
                            {B,w,B,B,B,w,B,w,w,B,w,w,w,B,B,w,w,w,B,w,B,B,B,w,B},
                            {B,w,w,w,w,w,B,w,B,B,w,B,B,w,w,B,w,w,B,w,w,w,w,w,B},
                            {B,B,B,B,B,B,B,w,B,w,B,w,B,w,B,w,B,w,B,B,B,B,B,B,B},
                            {w,w,w,w,w,w,w,w,w,B,B,B,w,w,B,B,w,w,w,w,w,w,w,w,w},
                            {B,B,B,B,B,w,B,B,B,B,w,B,w,w,w,w,B,B,w,B,w,B,w,B,w},
                            {B,B,w,B,w,w,w,w,B,w,B,w,B,B,w,w,w,B,w,w,w,w,B,B,w},
                            {w,B,B,w,B,B,B,B,B,w,B,w,w,B,B,B,B,w,w,B,w,w,w,w,B},
                            {w,B,w,B,w,w,w,w,B,w,w,w,B,B,w,B,B,B,B,B,w,B,w,B,B},
                            {w,B,B,B,B,w,B,B,B,B,B,w,B,w,B,B,B,w,B,B,B,w,B,w,w},
                            {B,B,w,w,w,w,w,B,w,B,w,w,w,w,w,w,w,B,w,w,w,B,w,w,w},
                            {B,w,B,w,w,B,B,w,w,B,w,B,B,w,w,B,B,w,B,B,w,w,B,B,B},
                            {B,w,w,B,B,B,w,w,B,B,B,B,w,w,B,w,w,w,w,w,w,B,w,w,B},
                            {B,w,w,w,w,w,B,B,w,B,w,B,w,w,w,B,B,B,B,B,B,B,B,w,B},
                            {w,w,w,w,w,w,w,w,w,B,B,w,B,B,B,w,B,w,w,w,B,w,B,B,w},
                            {B,B,B,B,B,B,B,w,B,B,w,w,w,B,B,w,B,w,B,w,B,B,B,B,B},
                            {B,w,w,w,w,w,B,w,w,w,w,w,B,B,w,B,B,w,w,w,B,B,w,B,w},
                            {B,w,B,B,B,w,B,w,B,B,B,w,B,w,B,B,B,B,B,B,B,w,B,w,B},
                            {B,w,B,B,B,w,B,w,B,w,B,w,w,w,w,w,w,w,B,B,B,B,w,B,B},
                            {B,w,B,B,B,w,B,w,B,B,B,B,B,w,w,w,w,B,w,w,w,w,w,w,B},
                            {B,w,w,w,w,w,B,w,B,w,w,B,w,w,B,w,B,B,B,w,w,B,w,w,B},
                            {B,B,B,B,B,B,B,w,B,B,B,B,w,w,w,B,w,w,w,B,w,w,B,B,B}
                            };
  
  QrMatrix *qrMatrix;
  qrMatrix = decodeQr((int*)qrCode, get_Width(qrCode));
                            
  TEST_ASSERT_EQUAL(0, strcmp("pi=3.14159265358979", qrMatrix->msg));
  TEST_ASSERT_EQUAL(2, qrMatrix->qrBitReaderInfo->version);
  TEST_ASSERT_EQUAL(2, qrMatrix->qrBitReaderInfo->format->maskType);
  TEST_ASSERT_EQUAL(LOW, qrMatrix->qrBitReaderInfo->format->eccLevel);
}

void test_version_5_qrcode_with_Byte_mode_and_Q_level_ecc_return_message_Dancing_in_the_pale_moonelight_dot(void){
  int qrCode [37][37] = {{B,B,B,B,B,B,B,w,B,w,w,B,w,w,w,B,w,w,B,w,w,B,w,w,w,B,w,w,B,w,B,B,B,B,B,B,B},
                         {B,w,w,w,w,w,B,w,w,B,B,w,w,B,w,w,w,B,B,w,B,B,B,B,B,B,B,B,B,w,B,w,w,w,w,w,B},
                         {B,w,B,B,B,w,B,w,w,B,B,B,B,w,B,B,B,w,B,w,B,B,w,B,w,B,w,w,B,w,B,w,B,B,B,w,B},
                         {B,w,B,B,B,w,B,w,w,B,w,B,w,w,w,w,B,B,B,B,w,w,B,B,B,w,B,w,w,w,B,w,B,B,B,w,B},
                         {B,w,B,B,B,w,B,w,B,w,B,B,w,B,w,B,w,w,B,B,B,B,w,w,w,B,w,w,w,w,B,w,B,B,B,w,B},
                         {B,w,w,w,w,w,B,w,B,w,B,B,w,w,w,w,w,w,w,B,B,w,B,B,B,B,B,B,B,w,B,w,w,w,w,w,B},
                         {B,B,B,B,B,B,B,w,B,w,B,w,B,w,B,w,B,w,B,w,B,w,B,w,B,w,B,w,B,w,B,B,B,B,B,B,B},
                         {w,w,w,w,w,w,w,w,w,w,B,B,B,B,w,B,w,B,w,w,w,B,B,B,w,B,w,w,B,w,w,w,w,w,w,w,w},
                         {w,B,B,B,B,B,B,B,w,w,w,B,B,w,B,w,B,B,B,B,w,w,B,B,B,w,B,B,B,w,w,B,B,w,w,w,B},
                         {B,B,B,B,w,w,w,B,w,w,B,B,w,w,B,B,B,w,B,w,B,B,w,B,w,w,w,B,w,w,B,B,B,B,w,w,B},
                         {B,w,B,B,B,B,B,w,w,B,B,w,B,w,w,B,w,B,B,B,B,B,w,w,w,w,w,B,B,w,B,w,B,w,w,w,B},
                         {B,B,B,B,w,w,w,w,B,B,B,w,B,B,B,w,w,w,w,w,w,B,B,w,B,w,w,B,w,B,w,B,B,B,w,w,w},
                         {w,w,B,w,B,B,B,B,B,w,w,w,w,B,w,B,w,w,w,w,w,B,w,B,w,B,B,B,B,B,B,w,w,w,w,B,w},
                         {w,B,w,w,w,B,w,w,w,w,w,B,B,B,w,B,w,B,w,w,B,B,B,B,w,B,w,B,w,w,w,B,B,w,w,B,w},
                         {B,B,B,B,B,w,B,w,B,w,B,B,w,B,B,w,B,w,w,B,B,B,w,w,B,B,B,B,B,B,B,w,B,B,w,B,B},
                         {w,B,w,B,w,w,w,B,w,B,B,B,w,w,B,w,w,w,w,B,B,B,B,w,B,w,B,B,w,B,B,B,B,w,w,w,B},
                         {w,w,B,B,w,B,B,w,B,B,w,w,B,w,w,B,B,w,B,B,B,B,w,w,w,B,B,B,w,w,B,w,B,B,B,w,B},
                         {B,w,B,B,w,B,w,w,B,B,B,w,B,B,B,B,w,w,B,w,B,w,B,w,B,w,w,w,B,w,w,B,w,B,w,w,B},
                         {w,w,w,w,B,w,B,B,B,w,w,w,w,B,B,B,B,w,w,B,B,B,w,w,w,w,w,B,B,w,B,w,w,B,w,B,B},
                         {B,w,w,B,w,B,w,B,B,B,B,B,B,w,B,w,B,B,w,B,B,B,w,w,B,w,B,B,B,B,B,B,B,w,w,w,w},
                         {B,B,w,w,B,w,B,B,B,w,B,w,B,B,B,B,w,w,B,B,w,w,B,w,w,w,w,w,w,w,B,w,B,B,B,B,w},
                         {B,B,B,w,w,B,w,B,B,w,B,B,B,B,w,B,B,w,w,w,B,w,w,w,B,w,B,w,B,B,B,B,w,w,B,w,B},
                         {B,w,B,w,B,w,B,B,B,w,B,w,w,w,w,w,B,B,w,w,w,B,w,w,w,w,w,B,w,w,B,w,B,B,B,B,w},
                         {B,B,B,B,B,B,w,w,w,B,B,B,B,w,w,w,w,B,w,B,w,B,w,w,B,w,B,w,B,B,B,B,B,w,B,w,w},
                         {B,w,B,w,w,B,B,B,w,B,B,w,B,B,w,w,w,w,B,B,w,w,B,w,B,w,w,w,w,w,B,B,w,B,w,B,w},
                         {w,w,w,w,B,B,w,w,w,B,w,B,B,w,w,B,B,w,w,B,w,w,B,B,w,B,B,B,B,B,B,w,w,w,B,w,w},
                         {w,B,B,B,B,w,B,B,w,B,w,B,w,B,w,B,B,B,B,w,B,w,B,w,B,w,w,w,w,w,w,B,w,B,B,w,B},
                         {w,B,w,B,w,w,w,w,w,w,w,B,B,B,w,B,w,w,w,w,w,w,w,w,w,w,B,w,B,B,B,w,w,w,B,w,B},
                         {w,B,w,w,w,w,B,B,B,B,w,w,B,w,w,w,B,B,B,B,w,B,B,B,B,B,B,w,B,B,B,B,B,B,w,B,B},
                         {w,w,w,w,w,w,w,w,B,B,w,B,B,w,B,w,B,B,B,w,w,w,w,B,B,B,w,B,B,w,w,w,B,B,w,w,w},
                         {B,B,B,B,B,B,B,w,B,w,B,w,w,w,w,w,B,w,w,w,B,w,B,w,B,B,B,B,B,w,B,w,B,w,w,w,B},
                         {B,w,w,w,w,w,B,w,B,B,w,w,w,B,w,B,B,B,w,w,w,w,w,B,w,w,w,w,B,w,w,w,B,w,w,B,B},
                         {B,w,B,B,B,w,B,w,B,w,B,B,w,w,B,w,w,B,w,w,B,B,B,B,B,B,B,w,B,B,B,B,B,B,B,B,B},
                         {B,w,B,B,B,w,B,w,B,B,B,B,B,B,B,w,w,B,B,w,w,B,w,w,w,B,w,B,B,B,B,B,w,B,w,B,B},
                         {B,w,B,B,B,w,B,w,B,B,B,w,B,B,B,B,w,B,B,w,B,B,w,B,B,B,B,w,B,w,w,w,w,w,w,w,B},
                         {B,w,w,w,w,w,B,w,B,B,w,B,w,w,w,w,w,w,B,w,w,B,B,B,w,B,w,B,B,w,B,B,w,w,w,w,B},
                         {B,B,B,B,B,B,B,w,w,w,w,B,w,w,B,B,B,w,B,w,B,B,w,B,B,w,B,w,w,w,B,w,w,B,B,B,B}
                         };
                         
  QrMatrix *qrMatrix;
  qrMatrix = decodeQr((int*)qrCode, get_Width(qrCode));
  
  TEST_ASSERT_EQUAL(0, strcmp("Dancing in the pale moonlight.", qrMatrix->msg));
  TEST_ASSERT_EQUAL(5, qrMatrix->qrBitReaderInfo->version);
  TEST_ASSERT_EQUAL(2, qrMatrix->qrBitReaderInfo->format->maskType);
  TEST_ASSERT_EQUAL(QUARTILE, qrMatrix->qrBitReaderInfo->format->eccLevel);
}

void xtest_dataArrange_for_QR_code_with_version_3_and_EC_level_HIGH(void){
  int data[26*8] = {0,0,0,0,0,0,0,0,
                    1,1,1,1,1,1,1,1,
                    2,2,2,2,2,2,2,2,
                    3,3,3,3,3,3,3,3,
                    4,4,4,4,4,4,4,4,
                    5,5,5,5,5,5,5,5,
                    6,6,6,6,6,6,6,6,
                    7,7,7,7,7,7,7,7,
                    8,8,8,8,8,8,8,8,
                    9,9,9,9,9,9,9,9,
                    10,10,10,10,10,10,10,10,
                    11,11,11,11,11,11,11,11,
                    12,12,12,12,12,12,12,12,
                    13,13,13,13,13,13,13,13,
                    14,14,14,14,14,14,14,14,
                    15,15,15,15,15,15,15,15,
                    16,16,16,16,16,16,16,16,
                    17,17,17,17,17,17,17,17,
                    18,18,18,18,18,18,18,18,
                    19,19,19,19,19,19,19,19,
                    20,20,20,20,20,20,20,20,
                    21,21,21,21,21,21,21,21,
                    22,22,22,22,22,22,22,22,
                    23,23,23,23,23,23,23,23,
                    24,24,24,24,24,24,24,24,
                    25,25,25,25,25,25,25,25};
  
  dataArrange((int*)data, 3, HIGH);
}

void xtest_dataArrange_for_QR_code_with_version_5_and_EC_level_Q(void){
  int data[62*8] = {0,0,0,0,0,0,0,0,
                    1,1,1,1,1,1,1,1,
                    2,2,2,2,2,2,2,2,
                    3,3,3,3,3,3,3,3,
                    4,4,4,4,4,4,4,4,
                    5,5,5,5,5,5,5,5,
                    6,6,6,6,6,6,6,6,
                    7,7,7,7,7,7,7,7,
                    8,8,8,8,8,8,8,8,
                    9,9,9,9,9,9,9,9,
                    10,10,10,10,10,10,10,10,
                    11,11,11,11,11,11,11,11,
                    12,12,12,12,12,12,12,12,
                    13,13,13,13,13,13,13,13,
                    14,14,14,14,14,14,14,14,
                    15,15,15,15,15,15,15,15,
                    16,16,16,16,16,16,16,16,
                    17,17,17,17,17,17,17,17,
                    18,18,18,18,18,18,18,18,
                    19,19,19,19,19,19,19,19,
                    20,20,20,20,20,20,20,20,
                    21,21,21,21,21,21,21,21,
                    22,22,22,22,22,22,22,22,
                    23,23,23,23,23,23,23,23,
                    24,24,24,24,24,24,24,24,
                    25,25,25,25,25,25,25,25,
                    26,26,26,26,26,26,26,26,
                    27,27,27,27,27,27,27,27,
                    28,28,28,28,28,28,28,28,
                    29,29,29,29,29,29,29,29,
                    30,30,30,30,30,30,30,30,
                    31,31,31,31,31,31,31,31,
                    32,32,32,32,32,32,32,32,
                    33,33,33,33,33,33,33,33,
                    34,34,34,34,34,34,34,34,
                    35,35,35,35,35,35,35,35,
                    36,36,36,36,36,36,36,36,
                    37,37,37,37,37,37,37,37,
                    38,38,38,38,38,38,38,38,
                    39,39,39,39,39,39,39,39,
                    40,40,40,40,40,40,40,40,
                    41,41,41,41,41,41,41,41,
                    42,42,42,42,42,42,42,42,
                    43,43,43,43,43,43,43,43,
                    44,44,44,44,44,44,44,44,
                    45,45,45,45,45,45,45,45,
                    46,46,46,46,46,46,46,46,
                    47,47,47,47,47,47,47,47,
                    48,48,48,48,48,48,48,48,
                    49,49,49,49,49,49,49,49,
                    50,50,50,50,50,50,50,50,
                    51,51,51,51,51,51,51,51,
                    52,52,52,52,52,52,52,52,
                    53,53,53,53,53,53,53,53,
                    54,54,54,54,54,54,54,54,
                    55,55,55,55,55,55,55,55,
                    56,56,56,56,56,56,56,56,
                    57,57,57,57,57,57,57,57,
                    58,58,58,58,58,58,58,58,
                    59,59,59,59,59,59,59,59,
                    60,60,60,60,60,60,60,60,
                    61,61,61,61,61,61,61,61};
  // printf("%d....", (sizeof(data)/sizeof(data[0])/8));
  dataArrange((int*)data, 5, QUARTILE);
}

void test_getTotalCodeword_with_version_1_and_EC_level_Low_return_19(void){
  int totalNumOfCodeword = getTotalCodeword(1, LOW);
  
  TEST_ASSERT_EQUAL(19, totalNumOfCodeword);
}

void test_getTotalCodeword_with_version_3_and_EC_level_QUARTILE_return_34(void){
  int totalNumOfCodeword = getTotalCodeword(3, QUARTILE);
  
  TEST_ASSERT_EQUAL(34, totalNumOfCodeword);
}

void test_getTotalCodeword_with_version_5_and_EC_level_QUARTILE_return_62(void){
  int totalNumOfCodeword = getTotalCodeword(5, QUARTILE);
  
  TEST_ASSERT_EQUAL(62, totalNumOfCodeword);
}
