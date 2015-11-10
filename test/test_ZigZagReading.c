#include "unity.h"
#include "ZigZagReading.h"

void setUp(void)
{
}

void tearDown(void)
{
}



/**
 *
 *    1   2
 *    3   4
 *    5   6    =======>   8,7,6,5,4,3,2,1
 *    7   8
 *
 */
void test_arr_upward_reading(void)
{
	int arr [4][2] = {{1,2},{3,4},{5,6},{7,8}};
  
  dataRetrive((int*)arr);
  
}
