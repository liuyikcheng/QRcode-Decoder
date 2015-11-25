#ifndef QRcodeDecode_H
#define QRcodeDecode_H
#include "QrMask.h"

typedef enum{
  NUMERIC,
  ALPHANUMERIC,
  BYTE
}Mode;

typedef struct{
  char eccLevel;
  MaskType maskType;
}Format;

typedef struct{
  int version;
  Format* format;
  Mode mode;
  char* message;
}QrMatrix;


typedef struct{
  int numberOfRow;
  int numberOfColumn;
}QrBitReaderInfo;

QrMatrix *decodeQr(int *qrMatrix, int width);
int getVersion(int width);
Format *getFormat(int *qrMatrix, int version);
Format *formatList(Format* format, int *formatMapTranslation);
int *unmaskFormatInfo(int* formatMapTranslation);

#endif // QRcodeDecode_H
