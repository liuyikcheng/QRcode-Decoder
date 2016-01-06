#include "unity.h"
#include "ZigZagReading.h"
#include "CustomAssertion.h"

#define getSize(x)  sizeof(x)/4

void setUp(void)
{
}

void tearDown(void)
{
}



/**
 *     down     up
 *    1   2   6   0 
 *    3   4   8   3  
 *    5   6   0   4    =======>   5,2,4,0,3,8,0,6,2,1,4,3,6,5,8,7
 *    7   8   2   5
 *
 */
void test_arr_reading(void)
{
	int arr [4][4] = {{1,2,6,0},{3,4,8,3},{5,6,0,4},{7,8,2,5}};
  int expected [16] = {5,2,4,0,3,8,0,6,2,1,4,3,6,5,8,7};
  int *data;
  data = dataRetrive((int*)arr, 4, 4);
  
  TEST_ASSERT_ARRAY(expected, data, 16);
}

/**
 *     up      down    up    
 *    1   2   6   0   0   9
 *    3   4   8   3   1   7
 *    5   6   0   4   8   2     =======>   3,9,2,8,7,1,9,0,0,6,3,8,4,0,5,2,8,7,6,5,4,3,2,1
 *    7   8   2   5   9   3
 *
 */
void test_arr_reading2(void)
{
	int arr [4][6] = {{1,2,6,0,0,9},{3,4,8,3,1,7},{5,6,0,4,8,2},{7,8,2,5,9,3}};
  int expected[24] = {3,9,2,8,7,1,9,0,0,6,3,8,4,0,5,2,8,7,6,5,4,3,2,1};
  int *data;
  data = dataRetrive((int*)arr, 4, 6);
  
  TEST_ASSERT_ARRAY(expected, data, 24);
}

/**
 *     up      down    up    
 *    1   2   6   0   0   9
 *    3   4   8   3   1   7
 *    5   6   0   4   8   2     =======>   1,7,1,6,3,9,2,8,7,1,9,0,0,6,3,8,4,0,5,2,2,4,1,7,8,0,9,3,8,7,6,5,4,3,2,1
 *    7   8   2   5   9   3
 *    3   9   4   2   6   1
 *    0   8   7   1   7   1
 *
 */
void test_arr_reading3(void)
{
	int arr [6][6] = {{1,2,6,0,0,9},{3,4,8,3,1,7},{5,6,0,4,8,2},{7,8,2,5,9,3},{3,9,4,2,6,1},{0,8,7,1,7,1}};
  int expected[36] = {1,7,1,6,3,9,2,8,7,1,9,0,0,6,3,8,4,0,5,2,2,4,1,7,8,0,9,3,8,7,6,5,4,3,2,1};
  int *data;
  data = dataRetrive((int*)arr, 6, 6);
  
  TEST_ASSERT_ARRAY(expected, data, 36);
}


