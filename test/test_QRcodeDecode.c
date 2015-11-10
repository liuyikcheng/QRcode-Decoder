#include "unity.h"
#include "QRcodeDecode.h"
#include <stdlib.h>

#define B   1
#define w   0

void setUp(void)
{
}

void tearDown(void)
{
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
