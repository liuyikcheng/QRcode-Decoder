#ifndef QRcodeDecode_H
#define QRcodeDecode_H
#include "QrMask.h"


typedef struct{
  char eccLevel;
  MaskType maskType;
}Format;

typedef enum{
  NUMERIC,
  ALPHANUMERIC,
  BYTE
}Mode;

typedef struct{
  int numberOfMsg;
  Mode mode;
  int *data;
  char *strData;
  int offset;
}QrBitReaderInfo;

typedef struct{
  int version;
  Format* format;
  QrBitReaderInfo* qrBitReaderInfo;
}QrMatrix;



QrMatrix *decodeQr(int *qrMatrix, int width);
int getVersion(int width);
Format *getFormat(int *qrMatrix, int version);
Format *formatList(Format* format, int *formatMapTranslation);
int *unmaskFormatInfo(int* formatMapTranslation);
char *arrayToString(int *data);
char *paddingByteRemove(char *data);

#endif // QRcodeDecode_H
