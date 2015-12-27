#include "QRcodeDecode.h"
#include "patternFilter.h"
#include "DataDecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define   ftm   formatMapTranslation
#define   getWidth(x)   x*4+17          // x = version of QR code

int apv1[] = {-1};
int apv2[] = {6,18,-1};
int *verAligPattern[] = {apv1,apv2};

// Number of Error Correction Code Words per block according to version and ECC level for version 1 to 5
int numOfECCodewords[] = {7,10,13,17,10,16,22,28,15,26,18,22,20,18,26,16,26,24,18,22};
int numOfDataCodeWordsG1[] = {19,16,13,9,34,28,22,16,55,44,17,13,80,32,24,9,108,43,15,11};
int numOfBlockG1[] = {1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,4,1,2,2,2};
int numOfDataCodeWordsG2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,12}; 
int numOfBlockG2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2};


/*@brief  To create QrBitReaderInfo structure
 *
 *@param  qrCode  The array of the QR code that is going to be decoded
 *        width   The width of the QR code
 *        
 *@retval qrBitReaderInfo   The structure of the info of QR code
 */
QrBitReaderInfo *createQrBitReaderInfo(int *qrCode, int width){
  
  QrBitReaderInfo *qrBitReaderInfo = malloc(sizeof(QrBitReaderInfo));
  qrBitReaderInfo->version = getVersion(width);
  qrBitReaderInfo->format = getFormat(qrCode,width);
  
  return qrBitReaderInfo;
}

/*@brief  To create QrMatrix structure
 *
 *@param  data              The data of the QR code which contains the message and error codes
 *        qrBitReaderInfo   The structure of the info of QR code
 *        
 *@retval qrMatrix          The structure contain all the info of QR code
 */
QrMatrix *createQrMatrix(int *data, QrBitReaderInfo *qrBitReaderInfo){
  
  QrMatrix *qrMatrix = malloc(sizeof(QrMatrix));
  qrMatrix->mode = getMode(data);
  qrMatrix->qrBitReaderInfo = qrBitReaderInfo;
  qrMatrix->msg = dataDecodeMsg(data, qrBitReaderInfo->version, (int)qrBitReaderInfo->format->eccLevel);
  
  return qrMatrix;
  
}

/*
 *
 *
 *
 */

QrMatrix *decodeQr(int *qrCode, int width){
  
  int* data;
  
  QrMatrix *qrMatrix;// = malloc(sizeof(QrMatrix));
  QrBitReaderInfo *qrBitReaderInfo = createQrBitReaderInfo(qrCode, width);// (malloc(sizeof(QrBitReaderInfo)));
  
  qrCode = unmaskAndPatternFilter(qrCode, width, qrBitReaderInfo);
  
  data = (int*)dataRetrive(qrCode, width, width);
  
  qrMatrix = createQrMatrix(data, qrBitReaderInfo);

  
  // errCorrectionDecode(qrBitReaderInfo, numOfDataCodewords[4*((qrMatrix->version)-1)+(int)qrMatrix->format->eccLevel]);
  

  return qrMatrix;
}

int *unmaskAndPatternFilter(int *qrCode, int width, QrBitReaderInfo *qrBitReaderInfo){
  
  qrCode = unmaskData(qrCode, width, width, qrBitReaderInfo->format->maskType);
  qrCode = leftTopFilter(qrCode, width, width);
  qrCode = rightTopFilter(qrCode, width, width);
  qrCode = leftBottomFilter(qrCode, width, width);
  qrCode = timingPatternFilter(qrCode, width, width);
  qrCode = darkModuleFilter(qrCode, width, width);
  qrCode = aligmentFilterVer(qrCode, qrBitReaderInfo->version);
  
  return qrCode;
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
    // printf("%d,", decimal);
    errCodeData[numOfErrDatacode] = decimal;
  }
  
  return errCodeData;
}


int *aligmentFilterVer(int *arr, int version){
  
  int *position;
  int i = 0, j = 0;
  position = verAligPattern[version-1];
  
  while(position[i] != -1){
    
    while(position[j] != -1){
      if(!((position[j] < 7)&&(position[i] < 7)) && \
      (!(position[j] <= getWidth(version) - 8)&&(position[i] > 7)) && \
      (!(position[i] <= getWidth(version) - 8)&&(position[j] > 7)) )
        arr = aligmentFilter(arr, getWidth(version), position[i], position[j]);
      // printf("(%d, %d)", position[i], position[j]);
      j++;
    }
    i++;
    j = 0;
  }
  
  return arr;
}

int dataArrange(int *data, int version, int errLevel){
  int *arragedData;
  int numOfBlock = numOfBlockG1[4*(version-1)+errLevel] + numOfBlockG2[4*(version-1)+errLevel];
  int i = 0, j = 0,k = 0, x = 0, block = 0, offset = 0, g1 = 0, g2 = 0;
  
  offset += (8*(numOfBlock-1));
  if (numOfBlock != 1){
    
    while (block < numOfBlockG1[4*(version-1)+errLevel]){
      
      while (g1 < numOfDataCodeWordsG1[4*(version-1)+errLevel]){
        
        for (x = 0; x < 8; x++){
          arragedData[i] = data[block+g1*offset+x];
          i++;
        }
        g1++;
      }
      
    }
  }
  // if ((numOfBlockG1[4*(version-1)+errLevel] != 1) && (numOfBlockG2[4*(version-1)+errLevel] != 0){
    
  // }
}
