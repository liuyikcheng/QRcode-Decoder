#include "DataDecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char *utf8Char[] =  {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "TAB", "LF", "VT", "FF", "CR", 
                             "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC",
                             "FS", "GS", "RS", "US", 
                             " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*",
                             "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                             ":", ";", "<", "=", ">", "?", "@",
                             "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "", "L", "M", "N", "O", "P", "Q", "R", 
                             "S", "T", "U", "V", "W", "X", "Y", "Z", 
                             "[", "\\", "]", "^", "_", "`",
                             "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s",
                             "t", "u", "v", "w", "x", "y", "z", 
                             "{", "|", "}", "~", "DEL" };
                             
char *alphaNumericChar[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H",
                            "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
                            " ", "$", "%", "*", "+", "-", ".", "/", ":"};

char eightBitsToChar(char *byte){
  int a = strtol(byte, NULL, 2);

  char c[100];
  sprintf(c,"0x%x",a);
 
  char wc = strtol(c, NULL, 16);
  
  return wc;
}

char *utf8Conversion(int *byte){
  
  char *str;
  int decimal = 0, i;
  for(i = 0; i < 8; i++){
    decimal = decimal + (((int)pow(2,i))*byte[7-i]);
  }
  
  str = utf8Char[decimal];
  
  return str;
}

Mode getMode(int *data){
  Mode mode;
  int decimal = 0, i;
  
  for(i = 0; i < 4; i++){
    decimal = decimal + (((int)pow(2,i))*data[3-i]);
  }
  
  switch(decimal){
    case 1: mode = NUMERIC; break;
    case 2: mode = ALPHANUMERIC; break;
    case 4: mode = BYTE; break;
  }
  
  
  return mode;
}

char *dataDecode(int *data){
  
}