#ifndef DataDecode_H
#define DataDecode_H

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
}QrBitReaderInfo;


char eightBinToChar(char *byte);
char *utf8Conversion(int *byte);
char *dataDecode(int *data);
Mode getMode(int *data);

#endif // DataDecode_H
