#ifndef QRcodeDecode_H
#define QRcodeDecode_H

int getFormatandVersion(int *qrMatrix, int size);
int getVersion(int width);
int getFormat(int *qrMatrix, int version);

// typedef struct{
  // int version;
  // int format;
  // char* message;
// }QRcode;
#endif // QRcodeDecode_H
