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

//QR code contains message "ABC 123456789" Byte mode, error correction level is L (7%)
void xtest_version_1_qrcode_return_message_ABC_123456789(void){
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
  
  // printf("...%d", (-1^1));
  TEST_ASSERT_EQUAL(1, qrMatrix->version);
  // TEST_ASSERT_EQUAL(7, qrMatrix->format->maskType);
  TEST_ASSERT_EQUAL('L', qrMatrix->format->eccLevel);
}

//Create a qr code 2d array matrix version 2
void xtest_example(void)
{
	int qrMatrix [25] [25] =  {{B,B,B,B,B,B,B,w,w,w,B,w,B,w,B,w,w,w,B,B,B,B,B,B,B},
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
                            
  // getFormatandVersion((int*)qrMatrix, sizeof(qrMatrix));
                            
                            
}
