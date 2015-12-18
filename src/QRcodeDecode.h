#ifndef QRcodeDecode_H
#define QRcodeDecode_H
#include "QrMask.h"

typedef enum{
  LOW,        // 	7% of codewords can be restored
  MEDIUM,     // 	15% of codewords can be restored
  QUARTILE,   // 	25% of codewords can be restored
  HIGH        // 	30% of codewords can be restored
}EccLevel;

typedef enum{
  NUMERIC,
  ALPHANUMERIC,
  BYTE
}Mode;

typedef struct{
  EccLevel eccLevel;
  MaskType maskType;
}Format;

typedef struct{
  int numberOfMsg;
  Mode mode;
  int *data;
  int *errCodeData;
  int offset;
}QrBitReaderInfo;

typedef struct{
  int version;
  Format* format;
  QrBitReaderInfo* qrBitReaderInfo;
  char msg[1000];
}QrMatrix;




QrMatrix *decodeQr(int *qrMatrix, int width);
int getVersion(int width);
Format *getFormat(int *qrMatrix, int version);
Format *formatList(Format* format, int *formatMapTranslation);
int *unmaskFormatInfo(int* formatMapTranslation);


#endif // QRcodeDecode_H
