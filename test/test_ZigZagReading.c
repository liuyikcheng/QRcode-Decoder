#include "unity.h"
#include "ZigZagReading.h"

#define getSize(x)  sizeof(x)/4

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
void xtest_arr_upward_reading(void)
{
	int arr [4][2] = {{1,2},{3,4},{5,6},{7,8}};
  int expected [8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int *data;
  data = dataRetriveUpward(arr, 4, 2);
  
}

/**
 *
 *    1   2
 *    3   4
 *    5   6    =======>   2,1,4,3,6,5,8,7
 *    7   8
 *
 */
void xtest_arr_downward_reading(void)
{
	int arr [4][2] = {{1,2},{3,4},{5,6},{7,8}};
  int expected [8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int *data;
  // data = dataRetriveDownward(arr, 4, 2);
  
}

/**
 *     down     up
 *    1   2   6   0 
 *    3   4   8   3  
 *    5   6   0   4    =======>   5,2,4,0,3,8,0,6,2,1,4,3,6,5,8,7
 *    7   8   2   5
 *
 */
void xtest_arr_reading(void)
{
	int arr [4][4] = {{1,2,6,0},{3,4,8,3},{5,6,0,4},{7,8,2,5}};
  int expected [8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int *data;
  data = dataRetrive(arr, 4, 4);
  
}

/**
 *     up      down    up    
 *    1   2   6   0   0   9
 *    3   4   8   3   1   7
 *    5   6   0   4   8   2     =======>   3,9,2,8,7,1,9,0,0,6,3,8,4,0,5,2,8,7,6,5,4,3,2,1
 *    7   8   2   5   9   3
 *
 */
void xtest_arr_reading2(void)
{
	int arr [4][6] = {{1,2,6,0,0,9},{3,4,8,3,1,7},{5,6,0,4,8,2},{7,8,2,5,9,3}};
  int *data;
  data = dataRetrive(arr, 4, 6);
  
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
void test_arr_reading2(void)
{
	int arr [6][6] = {{1,2,6,0,0,9},{3,4,8,3,1,7},{5,6,0,4,8,2},{7,8,2,5,9,3},{3,9,4,2,6,1},{0,8,7,1,7,1}};
  int *data;
  data = dataRetrive(arr, 6, 6);
  
}


