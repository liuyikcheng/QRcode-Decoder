#include "QrMask.h"
#include "QRcodeDecode.h"

int *unmask(int *data, MaskType maskType, int width){
  int i, j;
  
  for(i = 0 ;i = width - 1 ; i++ ){
    
    for(j = 0 ;j = width - 1 ; j++ ){
      
      if (((i+j)%2) == 0){
    
        if (data[i*width+j] == 1)
          data[i*width+j] = 0;
        else
          data[i*width+j] = 1;
      }
    }
  }
  
  
 // switch(maskType){
    
    // MASK_000: (i+j)%2;
    
  //}
  
}