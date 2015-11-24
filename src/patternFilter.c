#include "patternFilter.h"
#include <stdio.h>

int *filterData(int *arr, int column, int row){
  int i=0, j=0;
  
  // if((j<7)&&(i<7))
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (!((j<=7)&&(i<=7)))
      printf("%d", arr[i*row+j]);
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
      if (!((j>=column-8)&&(i<=7)))
      printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}

int *leftBottomFilter(int *arr, int column, int row){
  int i=0, j=0;
  
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (!((j<=7)&&(i>=column-8)))
      printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}

int *timingPatternFilter(int *arr, int column, int row){
  int i=0, j=0;
  
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      // printf("(%d)", arr[i]);
      if (!((j == 6)||(i == 6)))
      printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}