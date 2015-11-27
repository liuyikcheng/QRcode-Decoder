#include "patternFilter.h"
#include <stdio.h>

int *leftTopFilter(int *arr, int column, int row){
  int i=0, j=0;
  
  // if((j<7)&&(i<7))
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (((j<=7)&&(i<=7)))
        arr[i*row+j] = -1;
      // printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}

int *rightTopFilter(int *arr, int column, int row){
  int i=0, j=0;
  
  // if((j<7)&&(i<7))
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (((j>=column-8)&&(i<=7)))
        arr[i*row+j] = -1;
      // printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}

int *leftBottomFilter(int *arr, int column, int row){
  int i=0, j=0;
  
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (((j<=7)&&(i>=column-8)))
        arr[i*row+j] = -1;
      // printf("%d", arr[i*row+j]);
    }
  }
  
  
  return arr;
}

int *timingPatternFilter(int *arr, int column, int row){
  int i=0, j=0;
  
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (((j == 6)||(i == 6)))
        arr[i*row+j] = -1;
      // printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}

int *darkModuleFilter(int *arr, int column, int row){
  // printf("%d",arr[(column-8)*row+8]);
  arr[(column-8)*row+8] = -1;
  return arr;
}

int *aligmentFilter(int *arr, int row, int colMid, int rowMid){
  int i, j;
  
  for(i = colMid-2; i <= colMid+2; i++){
    for(j = colMid-2; j <= colMid+2; j++){
      arr[i*row+j] = -1;
      printf("%d,", arr[i*row+j]);
    }
  }
}