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
void dataDecode(int *data, QrBitReaderInfo *qrBitReaderInfo);
Mode getMode(int *data);

#endif // DataDecode_H
