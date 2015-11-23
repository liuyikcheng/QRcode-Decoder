#include "QrMask.h"
#include "QRcodeDecode.h"

int unmaskData

int *unmaskBit(int bit, int column, int row, MaskType maskType){
  
  switch(maskType){
    
    case MASK_000:  
      if((column+row)%2 == 0)
        bit = bit^1;
        break;
      
    case MASK_001:  
      if(column%2 == 0)
        bit = bit^1;
        break;
  }
  
  return bit;
}