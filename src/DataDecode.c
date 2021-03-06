#include "DataDecode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define verNerrlv(x,y)  4*(x - 1)+y

//character table
char *utf8Char[] =  {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "TAB",
                      "LF",  "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3",
                      "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", 
                      "RS", "US", " ", "!", "\"", "#", "$", "%", "&", "'",
                      "(", ")", "*", "+", ",", "-", ".", "/", "0", "1",
                      "2", "3", "4", "5", "6", "7", "8", "9", ":", ";",
                      "<", "=", ">", "?", "@", "A", "B", "C", "D", "E",
                      "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
                      "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y",
                      "Z", "[", "\\", "]", "^", "_", "`", "a", "b", "c",
                      "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                      "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
                      "x", "y", "z", "{", "|", "}", "~", "DEL" };
                             
char *alphaNumericChar[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H",
                            "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
                            " ", "$", "%", "*", "+", "-", ".", "/", ":"};
                            
//character count bits indicator by the coding mode
int countBit1to9[] = {10,9,8};  //version 1 to 9
int countBit10to26[] = {12,11,16};
int countBit27to40[] = {14,13,16};

//each character bit based on different coding mode
int charBit[] = {10,11,8};
                            
// Character Capacities by Version, Mode, and Error Correction, until version 20 only
int numericCap[] = {41, 34, 27, 17, 77, 63, 48, 34, 127, 101,77,58,187,149,111,82,255,202,144,106,322,255,178,139,370,293,207,154,461,365,259,202,
                    552,432,312,235,652,513,364,288,772,604,427,331,883,691,489,374,1022,796,580,427,1101,871,621,468,1250,991,703,530,1408,1082,
                    775,602,1548,1212,876,674,1725,1346,948,746,1903,1500,1063,813,2061,1600,1159,919};
int alphanumericCap[] = {25,20,16,10,47,38,29,20,77,61,47,35,114,90,67,50,154,122,87,64,195,154,108,84,224,178,125,93,279,221,157,122,335,262,189,
                          143,395,311,221,174,468,366,259,200,535,419,296,227,619,483,352,259,667,528,376,283,758,600,426,321,854,656,470,365,938,
                          734,531,408,1046,816,574,452,1153,909,644,493,1249,970,702,557};
int byteCap[] = {17,14,11,7,32,26,20,14,53,42,32,24,78,62,46,34,106,84,60,44,134,106,74,58,154,122,86,64,192,152,108,84,230,180,130,98,271,213,151,
                  119,321,251,177,137,367,287,203,155,425,331,241,177,458,362,258,194,520,412,292,220,586,450,322,250,644,504,354,280,718,560,394,
                  310,792,624,442,338,858,666,482,382};
                 


/*@brief    The function to convert binary string to UTF-8 character
 *
 *@param    byte    The binary string data to decode
 *          offset  The position of bit start to be process
 *
 *@retval   str     Decoded character
 */
char *utf8Conversion(int *byte, int offset){
  
  char *str;
  int decimal = 0, i;
  for(i = 0; i < 8; i++){
    decimal = decimal + (((int)pow(2,i))*byte[7-i+offset]);
    // printf("%d", byte[7-i+offset]);
  }

  str = utf8Char[decimal];
  
  return str;
}

/*@brief    The function to convert binary string to numeric character
 *
 *@param    numData     The binary string data to decode
 *          offset      The position of bit start to be process
 *          numOfDigit  Number of digit in the binary string
 *@retval   str         Decoded characters
 */ 
char *numericConversion(int *numData, int offset, int numOfDigit){
  
  char *str = malloc(sizeof(char)*numOfDigit);
  int i, decimal = 0;
  
  for(i = 0; i < (10-3*(3-numOfDigit)); i++){
    decimal = decimal + (((int)pow(2,i))*numData[(10-3*(3-numOfDigit))-1-i+offset]);
  }
  sprintf(str, "%d", decimal);
  // printf("%d", decimal);
  return str;
  
}

/*@brief    The function to convert binary string to alphanumeric character
 *
 *@param    alpnumData  The binary string data to decode
 *          offset      The position of bit start to be process
 *          even        1   The data contain even number of character
 *                      0   The data contain odd number of character
 *@retval   str         Decoded characters
 */ 
char *alpnumConversion(int *alpnumData, int offset, int even){
  
  char *str = malloc(sizeof(char)*2);
  int decimal = 0, val1, val2, i;
  
  for(i = 0; i < (6+5*even); i++){
    decimal = decimal + (((int)pow(2,i))*alpnumData[(6+5*even-1)-i+offset]);
  }

  if(even){
    val1 = decimal / 45;
    val2 = decimal % 45;
    sprintf(str, "%s%s", alphaNumericChar[val1], alphaNumericChar[val2]);
  }
  else
    str = alphaNumericChar[decimal];
  
  return str;
}


/*@brief    The function to identify the coding mode of the data
 *
 *@param    data    The binary string data to decode
 *          
 *@retval   mode    The data coding mode
 */ 
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

int getNumOfChar(int *data, int mode, int offset, int countBit){
  int i, numOfChar = 0;
  
   for(i = 0; i < countBit; i++){
    numOfChar = numOfChar + (((int)pow(2,i))*data[offset+countBit-i-1]);
    // printf("%d,", data[offset+countBit-i-1]);
  }
  
  return numOfChar;
}

/*@brief    The function to find out the number of count bit of the data
 *
 *@param    mode              The mode of the coding
 *          version           The version of the QR code
 *          
 *@retval   countBit          The number of the count bit
 */ 
int getNumOfCountBit(int mode, int version){
  
  int countBit;
  
  if (version <= 9){
    countBit = countBit1to9[mode];
  }
  else if ((version >= 10) && (version <= 26)){
    countBit = countBit10to26[mode];
  }
  else if ((version >= 27) && (version <= 40)){
    countBit = countBit27to40[mode];
  }
  
  return countBit;
}

/*@brief    The function to find out the Character Capacities by Version, Mode, and Error Correction
 *
 *@param    mode              The mode of the coding
 *          version           The version of the QR code
 *          errLevel          The error correction level of the QR code
 *          
 *@retval   charCap           The value of character capacity
 */ 
int getCharCap(int mode, int version, int errLevel){
  
   int charCap;
  
  if (mode == NUMERIC){
    charCap = numericCap[verNerrlv(version,errLevel)];
  }
  else if (mode == ALPHANUMERIC){
    charCap = alphanumericCap[verNerrlv(version,errLevel)];
  }
  else if (mode == BYTE){
    charCap = byteCap[verNerrlv(version,errLevel)];
  }
  
  return charCap;
}

/*@brief    The function to decode the binary message
 *
 *@param    data              The binary string data is extracted from QR code
 *          mode              The mode of the coding
 *          offset            The offset of the binary string
 *          countBit          The number of the count bit
 *          charCap           The value of character capacity
 *
 *@retval   str               The string data from the code
 */ 
char *msgDecode(int *data, int mode, int offset, int countBit, int charCap){
  
  char *str = malloc(sizeof(char)*charCap);
  int i = 0, numOfChar = 0;
  int bitPerChar = charBit[mode];
  str[0] = '\0';
  
  numOfChar = getNumOfChar(data, mode, offset, countBit);


  offset += countBit;
  
  i = 0;
  while (i < (numOfChar)){
    
    switch(mode){
      case NUMERIC:       if ((numOfChar%3 != 0)&&(numOfChar-i == 2))
                            sprintf(str, "%s%s", str, numericConversion(data, offset, 2));
                          else if ((numOfChar%3 != 0)&&(numOfChar-i == 1))
                            sprintf(str, "%s%s", str, numericConversion(data, offset, 1));
                          else
                            sprintf(str, "%s%s", str, numericConversion(data, offset, 3));
                          i += 3;
                          break;
      case ALPHANUMERIC:  if ((numOfChar%2 != 0)&&(i == numOfChar - 1))
                            sprintf(str, "%s%s", str, alpnumConversion(data, offset, ODD));
                          else
                            sprintf(str, "%s%s", str, alpnumConversion(data, offset, EVEN));  
                          i += 2;
                          break;
      case BYTE:          sprintf(str, "%s%s", str, utf8Conversion(data, offset));
                          // printf("%s", utf8Conversion(data, offset));
                          // strcat(str,utf8Conversion(data, offset));
                          i++;
                          break;
    }
    offset += bitPerChar;
  }
  // printf("%s", str);
  return str;
}



