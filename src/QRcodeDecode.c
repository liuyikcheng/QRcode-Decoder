#include "QRcodeDecode.h"
#include "patternFilter.h"
#include "DataDecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define   ftm   formatMapTranslation



// Number of Error Correction Code Words per block according to version and ECC level for version 1 to 5
int numOfDataCodewords[] = {7,10,13,17,10,16,22,28,15,26,18,22,20,18,26,16,26,24,18,22};

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
  
  int *a;
  
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

  // qrBitReaderInfo->strData = malloc(sizeof(char)*100);
  sprintf(qrMatrix->msg,"%s", dataDecode(qrBitReaderInfo->data, qrBitReaderInfo));
  
  // printf("\n%s",dataDecode(qrBitReaderInfo->data, qrBitReaderInfo));
  // printf("\n%s",qrMatrix->msg);
  
  
  
  errCorrectionDecode(qrBitReaderInfo, numOfDataCodewords[4*((qrMatrix->version)-1)+(int)qrMatrix->format->eccLevel]);
  
  for(i=0;i<7;i++){
    
  // printf("%d", qrBitReaderInfo->errCodeData[i]);
  }
  qrMatrix->qrBitReaderInfo = qrBitReaderInfo;
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
    format->eccLevel = LOW;
  else if ((ftm[14] == 0)&&(ftm[13] == 0)) 
    format->eccLevel = MEDIUM;
  else if ((ftm[14] == 1)&&(ftm[13] == 1)) 
    format->eccLevel = QUARTILE;
  else if ((ftm[14] == 1)&&(ftm[13] == 0)) 
    format->eccLevel = HIGH;
  
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


int *errCorrectionDecode(QrBitReaderInfo *qrBitReaderInfo, int numOfErrDatacode){
  int i, j, decimal = 0;
  int *errCodeData = malloc(sizeof(int)*numOfErrDatacode-1);

  
  while (qrBitReaderInfo->data[i] != -1){
    i++;
  }
  // printf("%d\n", i);
  
  for (numOfErrDatacode = numOfErrDatacode-1; numOfErrDatacode >= 0; numOfErrDatacode--){
    i = i - 8;
    decimal = 0;
    
    for (j = 0; j < 8; j++){
      // printf("%d", qrBitReaderInfo->data[i+j]);
      
      decimal = decimal + (((int)pow(2,j))*qrBitReaderInfo->data[i+(7-j)]);
    }
    printf("%d,", decimal);
    errCodeData[numOfErrDatacode] = decimal;
  }
  
  return errCodeData;
}


