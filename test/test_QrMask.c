#include "unity.h"
#include "QrMask.h"
#include "QRcodeDecode.h"

void setUp(void)
{
}

void tearDown(void)
{
}




/*
 *        1 0 1 0 1 0 1 0           1 1 1 1                               0 1 0 1
 *        0 1 0 1 0 1 0 1           0 0 1 0   (1111001011010000) ======>  0 1 1 1   (0101011101110101)
 *        1 0 1 0 1 0 1 0           1 1 0 1                               0 1 1 1
 *        0 1 0 1 0 1 0 1           0 0 0 0                               0 1 0 1
 *
 *          (x+y)%2 = 0
 *           MASK 000
 */
void test_Mask_000(void)
{
	int data[16] = {1,1,1,1,0,0,1,0,1,1,0,1,0,0,0,0};
  
}
