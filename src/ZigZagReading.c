#include "ZigZagReading.h"
#include <stdio.h>
#include <stdlib.h>



/**
 *@brief    To retrieve the data in zig-zag motion
 *
 *@param    arr       The 2d data array
 *          column    The column size of the data
 *          row       The row size of the data
 *
 *@retval   data      The retrieved data from the 2d array
 */
int *dataRetrive(int *arr, int column, int row){
  int *data = malloc((column+row)*10000);
  int i = column-1, j = row-1, k = 0, rowData = row-1;
  
  
  while(rowData >= 0){
    i = column-1;
    
    while((i >= 0)&&(rowData >= 0)){
      
      for(j = rowData ; j >= rowData - 1 ; j --){
        // printf("(%d,%d) ", j, i);
        
        if ((arr[i*row+j] >= 0)&&(i >= 0)&&(j >= 0)){
          data[k] = arr[i*row+j];
          // printf("%d,", data[k]);
          k++;
        }
      }
      i--;
    }
    // printf("\n");
    rowData = rowData - 2;
    if (rowData == 6) // ignore the vertical timing pattern
      rowData --;
    
    i = 0;
    
    while((i <= column-1)&&(rowData >= 0)){
      
      for(j = rowData ; j >= rowData - 1 ; j --){
        // printf("(%d,%d) ", j, i);
        if ((arr[i*row+j] >= 0)&&(i >= 0)&&(j >= 0)){
          data[k] = arr[i*row+j];
          // printf("%d,", data[k]);
          // printf("[%d]", k);
          k++;
        }
      }

      i++;
    }
    rowData = rowData - 2;
    // printf("\n");
  }
  
  data[k] = -1;
  
  return data;
}