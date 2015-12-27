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
}