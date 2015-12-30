#include "ZigZagReading.h"
#include <stdio.h>
#include <stdlib.h>

Data *createData(){
  int i;
  Data *data = malloc(sizeof(Data));
  data->next = NULL;
  return data;
}

/**
 *
 *
 *
 *
 *
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

int *dataRetriveUpward(int *arr, int column, int row){
  int *data = malloc((column+row)*8);
  int i, j, k = 0;
  
  for(i = (column - 1); i >= 0 ; i--){
    for(j = (row - 1); j >= (row - 2) ; j--){
      data[k] = arr[i*row+j];
      k++;
    }
  }
  
  for(i = 0; i <= (7) ; i++){
    // printf("%d", data[i]);
  }
  
  return data;
}

int *dataRetriveDownward(int *arr, int column, int row){
  int *data = malloc((column+row)*8);
  int i, j, k = 0;
  
 for(i = 0 ; i <= (column - 1) ; i++){
    for(j = (row-2-1); j >= (row-2-2) ; j--){
      data[k] = arr[i*row+j];
    // printf("%d", arr[i*row+j]);
      k++;
    }
  }
  
  for(i = 0; i <= 7 ; i++){
    // printf("%d", data[i]);
  }
  
  return data;
}