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
  int version;
  Format* format;
  int *data;
  Mode mode;
  int numOfChar;
  char* msg;
}QrBitReaderInfo;

typedef struct{
  QrBitReaderInfo* qrBitReaderInfo;
  Mode mode;
  char *msg;
  int *errCodeData;
}QrMatrix;

int *unmaskAndPatternFilter(int *qrCode, int width, QrBitReaderInfo *qrBitReaderInfo);
QrMatrix *createQrMatrix(int *data, QrBitReaderInfo *qrBitReaderInfo);
QrBitReaderInfo *createQrBitReaderInfo(int *qrCode, int width);
QrMatrix *decodeQr(int *qrMatrix, int width);
int getVersion(int width);
Format *getFormat(int *qrMatrix, int version);
Format *formatList(Format* format, int *formatMapTranslation);
int *unmaskFormatInfo(int* formatMapTranslation);
int *aligmentFilterVer(int *arr, int version);
int *dataArrange(int *data, int version, int errLevel);
int getTotalCodeword(int version, int errLevel);
int *errCodeDataArrange(int *data, int version, int errLevel);
void placeErrorCodeword(unsigned char msg[], int* errorCodeword, unsigned char codeword[],int numOfChar, int numOfECC);
char *dataDecodeMsg(int* data, int version, int errLevel, int *numOfChar);

#endif // QRcodeDecode_H
