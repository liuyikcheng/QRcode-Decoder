#ifndef ZigZagReading_H
#define ZigZagReading_H

int *dataRetriveUpward(int *arr, int column, int row);
int *dataRetriveDownward(int *arr, int column, int row);
int *dataRetrive(int *arr, int column, int row);

typedef struct Data_t Data;

struct Data_t{
  int dataByte [8];
  Data *next;
};

Data *createData();

#endif // ZigZagReading_H
