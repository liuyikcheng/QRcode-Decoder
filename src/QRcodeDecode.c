#include "QRcodeDecode.h"
#include <stdio.h>
#include <math.h>

int getFormatandVersion(int *qrMatrix, int size){
  int count = 0;
  int i, j = 0;
  int version, format, width;
  
  width = sqrt(size/4);
  
  version = getVersion(width);
  format = getFormat(qrMatrix,width);

}

int getFormat(int *qrMatrix, int width){
  int formatMapTranslation [15];
  int formatMapTranslation2 [15];
  int i = 0, j = 14;
  int range = 0;
  
  
  // Horizontal format info
  for(i = 0; i <= 15; i++){
    
    if(i == 8)
      range = width - 16;
    
    if(i != 6){
      formatMapTranslation[j] = *(qrMatrix+i+8*width+range);
      j--;
    }
  }
  
  range = 0;
  
  // Vertical format info
  for(i = 0; i <= 14 ; i++){
      formatMapTranslation2[i] = *(qrMatrix+8+range);
    if(i == 5)
      range = range + 2*width;
    else if(i == 7)
      range = range + (width-15)*width;
    else
      range = range + width;
    
  }
  
  for(i = 0; i<= 14; i++){
    if(formatMapTranslation[i] != formatMapTranslation2[i])
      printf("Error format bit unmatch");;
    // printf("%d",formatMapTranslation2[i]);
  }
  return 0 ;
}

int getVersion(int width){
  int version;
  version = (width-17)/4;
  return version;
}