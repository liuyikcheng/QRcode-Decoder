#ifndef QrMask_H
#define QrMask_H



typedef enum{
  MASK_000,
  MASK_001,
  MASK_010,
  MASK_011,
  MASK_100,
  MASK_101,
  MASK_110,
  MASK_111,
  
}MaskType;

int *unmaskData(int *arr, int column, int row, MaskType maskType);
int unmaskBit(int bit, int column, int row, MaskType maskType);


#endif // QrMask_H
