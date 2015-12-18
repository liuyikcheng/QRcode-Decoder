#include "QrMask.h"
// #include "QRcodeDecode.h"
#include <stdio.h>

int *unmaskData(int *arr, int column, int row, MaskType maskType){
  int i=0, j=0;
  
  for(i = 0; i < column ; i++){
    for(j = 0; j < row ; j++){
      arr[i*row+j] = unmaskBit(arr[i*row+j], i, j, maskType);
      // printf("(%d)", arr[i]);
      // printf("%d", arr[i*row+j]);
    }
  }
  
  return arr;
}

int unmaskBit(int bit, int column, int row, MaskType maskType){
  
  switch(maskType){
    
    case MASK_000:  
      if((column+row)%2 == 0)
        bit = bit^1;
        break; 
    case MASK_001:  
      if(column%2 == 0)
        bit = bit^1;
        break;
    case MASK_010:  
      if(row%2 == 0)
        bit = bit^1;
        break;
    case MASK_011:  
      if((column+row)%3 == 0)
        bit = bit^1;
        break;
    case MASK_100:  
      if((column/2+row/3)%2 == 0)
        bit = bit^1;
        break;
    case MASK_101:  
      if(((column*row)%2)+((column*row)%3) == 0)
        bit = bit^1;
        break;
    case MASK_110:  
      if(((column*row)%3+column*row)%2 == 0)
        bit = bit^1;
        break;
    case MASK_111:  
      if(((column*row)%3+column+row)%2 == 0)
        bit = bit^1;
        break;
  }
  
  return bit;
}