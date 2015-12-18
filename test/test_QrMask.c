#include "unity.h"
#include "QrMask.h"
// #include "QRcodeDecode.h"

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
 *        (column+row)%2 == 0
 *           MASK 000
 */
void test_Mask_000(void)
{
	int data[4][4] = {{1,1,1,1},
                  {0,0,1,0},
                  {1,1,0,1},
                  {0,0,0,0}};
  int *unmakedData;
  unmakedData = unmaskData((int*)data, 4, 4, MASK_000);
}

/*
 *        1 1 1 1 1 1 1 1           1 1 1 1                               0 0 0 0
 *        0 0 0 0 0 0 0 0           0 0 1 0   (1111001011010000) ======>  0 0 1 0   (0000001000100000)
 *        1 1 1 1 1 1 1 1           1 1 0 1                               0 0 1 0
 *        0 0 0 0 0 0 0 0           0 0 0 0                               0 0 0 0
 *
 *          column%2 == 0
 *           MASK 001
 */
void test_Mask_001(void)
{
	int data[4][4] = {{1,1,1,1},
                  {0,0,1,0},
                  {1,1,0,1},
                  {0,0,0,0}};
  int *unmakedData;
  unmakedData = unmaskData((int*)data, 4, 4, MASK_001);
}

/*
 *        1 0 1 0 1 0 1 0           1 1 1 1                               0 1 0 1
 *        1 0 1 0 1 0 1 0           0 0 1 0   (1111001011010000) ======>  1 0 0 0   (0101100001111010)
 *        1 0 1 0 1 0 1 0           1 1 0 1                               0 1 1 1
 *        1 0 1 0 1 0 1 0           0 0 0 0                               1 0 1 0
 *
 *        (column+row)%2 == 0
 *           MASK 000
 */
void test_Mask_010(void)
{
	int data[4][4] = {{1,1,1,1},
                  {0,0,1,0},
                  {1,1,0,1},
                  {0,0,0,0}};
  int *unmakedData;
  unmakedData = unmaskData((int*)data, 4, 4, MASK_010);
}
