#include "unity.h"
#include "QRcodeDecode.h"
#include "ZigZagReading.h"
#include <stdlib.h>

#define B   1
#define w   0

void setUp(void)
{
}

void tearDown(void)
{
}

//QR code contains message "ABC 123456789" 8bit mode, error correction level is L (7%)
void test_version_1_qrcode_return_message_ABC_123456789(void){
    int qrMatrix [21] [21] = {{B,B,B,B,B,B,B,w,w,B,w,B,B,w,B,B,B,B,B,B,B},
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
  dataRetrive(qrMatrix, 21, 21);
}

//Create a qr code 2d array matrix version 2
void test_example(void)
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
                            
  getFormatandVersion((int*)qrMatrix, sizeof(qrMatrix));
                            
                            
}
