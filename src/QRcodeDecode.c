#include "QRcodeDecode.h"
#include "patternFilter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define   ftm   formatMapTranslation

/*
 *
 *
 *
 */

QrMatrix *decodeQr(int *qrCode, int width){
  
  QrMatrix *qrMatrix = malloc(sizeof(QrMatrix));
  QrBitReaderInfo *qrBitReaderInfo = (malloc(sizeof(QrBitReaderInfo)));
  int count = 0;
  int i, j = 0;
  
  
  qrMatrix->version = getVersion(width);
  qrMatrix->format = getFormat(qrCode,width);
  
  //unmask the data
  qrCode = unmaskData(qrCode, width, width, qrMatrix->format->maskType);
  
  //filter the pattern
  qrCode = leftTopFilter(qrCode, width, width);
  qrCode = rightTopFilter(qrCode, width, width);
  qrCode = leftBottomFilter(qrCode, width, width);
  qrCode = timingPatternFilter(qrCode, width, width);
  qrCode = darkModuleFilter(qrCode, width, width);
  
  qrBitReaderInfo->data = (int*)dataRetrive(qrCode, width, width);
  qrBitReaderInfo->strData = arrayToString(qrBitReaderInfo->data);
  
  return qrMatrix;
}

/* @brief   To get the format info of QR code
 *
 *
 *
 */
Format *getFormat(int *qrMatrix, int width){
  Format *format;
  int ftm [15];
  int ftm2 [15];
  int i = 0, j = 14;
  int range = 0;
  
  
  // Horizontal format info
  for(i = 0; i <= 15; i++){
    
    if(i == 8)
      range = width - 16;
    
    if(i != 6){
      ftm[j] = *(qrMatrix+i+8*width+range);
      *(qrMatrix+i+8*width+range) = -1;
      j--;
    }
  }
  
  range = 0;
  
  // Vertical format info
  for(i = 0; i <= 14 ; i++){
    
      ftm2[i] = *(qrMatrix+8+range);
      *(qrMatrix+8+range) = -1;
      
    if(i == 5)
      range = range + 2*width;
    else if(i == 7)
      range = range + (width-15)*width;
    else
      range = range + width;
    
  }
  
  for(i = 0; i<= 14; i++){
    
    if(ftm[i] != ftm2[i])
      printf("Error format bit unmatch");
  }
  
  format = formatList(format, ftm);
  
  return format ;
}

/* @brief   To get the version info of QR code
 *
 *
 *
 */
int getVersion(int width){
  int version;
  version = (width-17)/4;
  return version;
}

/* @brief   To get the error correction level and the mask pattern of QR code
 *
 *
 *
 */
Format *formatList(Format* format, int *ftm){
  char formatStr[16];
  int i, index = 0;
  
  ftm = unmaskFormatInfo(ftm);
  
  
  for (i = 0; i < 15; i++)   // convert int array to string
    index += sprintf(&formatStr[index], "%d", ftm[i]);
    
  if ((ftm[14] == 0)&&(ftm[13] == 1))
    format->eccLevel = 'L';
  else if ((ftm[14] == 0)&&(ftm[13] == 0)) 
    format->eccLevel = 'M';
  else if ((ftm[14] == 1)&&(ftm[13] == 1)) 
    format->eccLevel = 'Q';
  else if ((ftm[14] == 1)&&(ftm[13] == 0)) 
    format->eccLevel = 'H';
  
  if ((ftm[12] == 0)&&(ftm[11] == 0)&&(ftm[10] == 0))
    format->maskType = MASK_000;
  else if ((ftm[12] == 0)&&(ftm[11] == 0)&&(ftm[10] == 1))
    format->maskType = MASK_001;
  else if ((ftm[12] == 0)&&(ftm[11] == 1)&&(ftm[10] == 0))
    format->maskType = MASK_010;
  else if ((ftm[12] == 0)&&(ftm[11] == 1)&&(ftm[10] == 1))
    format->maskType = MASK_011;
  else if ((ftm[12] == 1)&&(ftm[11] == 0)&&(ftm[10] == 0))
    format->maskType = MASK_100;
  else if ((ftm[12] == 1)&&(ftm[11] == 0)&&(ftm[10] == 1))
    format->maskType = MASK_101;
  else if ((ftm[12] == 1)&&(ftm[11] == 1)&&(ftm[10] == 0))
    format->maskType = MASK_110;
  else if ((ftm[12] == 1)&&(ftm[11] == 1)&&(ftm[10] == 1))
    format->maskType = MASK_111;
  
  // printf("%s", formatStr);
  
  return format;
}

/* @brief   To unmask format bits of QR code
 *
 *
 *
 */
int *unmaskFormatInfo(int* ftm){
  int i;
  
  for(i = 0 ; i < 15; i++){
    
    // if((i == 0)||(i == 2)||(i == 4)||(i == 10)||(i == 13))
       if((i == 14)||(i == 12)||(i == 10)||(i == 4)||(i == 1))
      ftm[i] = ftm[i]^1;
  }
  return ftm;
}

/* @brief   To determine the decoding mode of QR code
 *
 *
 *
 */
char *arrayToString(int *data){
  int i = 0;
  char *str = malloc(1000);
  
  while(data[i] != -1){
    // printf("%d", data[i]);
    sprintf(&str[i], "%d", data[i]);
    i++;
  }
  
  paddingByteRemove(str);
  
  
  return str;
}

char *paddingByteRemove(char *strData){
  char *byteData = malloc(8);
  char *errCode = malloc(1000);
  int i = 0, j = 0, k = 0, errCodeBit; 
  
  while (i < strlen(strData)){

    while (j < 8){
    sprintf(&byteData[j], "%c", strData[i+j]);
    j++;
    }
    printf("%s\n", byteData);
    i += 8;
    
    if((strcmp("11101100", byteData) == 0) || (strcmp("00010001", byteData) == 0)){
      errCodeBit = i+j;
    }
    
    j = 0;
  }
}

Mode decodeMode(char strData){
  
}