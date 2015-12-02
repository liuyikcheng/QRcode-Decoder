#include "DataDecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char eightBinToChar(char *byte){
  int a = strtol(byte, NULL, 2);

  char c[100];
  sprintf(c,"0x%x",a);

  
  char wc = strtol(c, NULL, 16);
  
  return wc;
}