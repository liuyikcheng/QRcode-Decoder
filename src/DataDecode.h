#ifndef DataDecode_H
#define DataDecode_H
#include "QRcodeDecode.h"
// typedef enum{
  // NUMERIC,
  // ALPHANUMERIC,
  // BYTE
// }Mode;

// typedef struct{
  // int numberOfMsg;
  // Mode mode;
  // int *data;
  // char *strData;
  // int offset;
// }QrBitReaderInfo;

char *utf8Conversion(int *byte, int offset);
char *alpnumConversion(int *alpnumData, int offset, int even);
char *numericConversion(int *numData, int offset, int numOfDigit);
Mode getMode(int *data);
int *errCorrectionDecode(QrBitReaderInfo *qrBitReaderInfo, int numOfErrDatacode);
int getNumOfChar(int *data, int mode, int offset, int countBit);
int getNumOfCountBit(int mode, int version);
int getCharCap(int mode, int version, int errLevel);
char *msgDecode(int *data, int mode, int offset, int countBit, int charCap);


#define ODD   0
#define EVEN  1

#define NUMERIC       0
#define ALPHANUMERIC  1
#define BYTE          2

#define L       0
#define M       1
#define Q       2
#define H       3

#endif // DataDecode_H
