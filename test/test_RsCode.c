#include "unity.h"
#include "RsCode.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_rsCode(void){
  
  unsigned char msg[] = "Nervously I loaded the twin ducks aboard the revolving pl\
        atform.";
  unsigned char codeword[256];
  
  int erasures[16];
  int nerasures = 0;

  /* Initialization the ECC library */
 
  initialize_ecc ();
 
  /* ************** */
 
  /* Encode data into codeword, adding NPAR parity bytes */
  printf("Message : %s\n", msg);
  encode_data(msg, sizeof(msg), codeword);
 
  printf("Encoded data is: \"%s\"\n", codeword);
  
  int i;
  for(i = 0; i<256; i++){
    // printf("%d", codeword[i]);
  }
 
#define ML (sizeof (msg) + NPAR)


  /* Add one error and two erasures */
  byte_err(0x35, 3, codeword);

  byte_err(0x23, 17, codeword);
  byte_err(0x34, 19, codeword);


  printf("with some errors: \"%s\"\n", codeword);

  /* We need to indicate the position of the erasures.  Eraseure
     positions are indexed (1 based) from the end of the message... */

  erasures[nerasures++] = ML-17;
  erasures[nerasures++] = ML-19;

 
  /* Now decode -- encoded codeword size must be passed */
  decode_data(codeword, ML);

  /* check if syndrome is all zeros */
  if (check_syndrome () != 0) {
    correct_errors_erasures (codeword, 
			     ML,
			     nerasures, 
			     erasures);
 
    printf("Corrected codeword: \"%s\"\n", codeword);
  }
  
}
void
byte_err (int err, int loc, unsigned char *dst)
{
  printf("Adding Error at loc %d, data %#x\n", loc, dst[loc-1]);
  dst[loc-1] ^= err;
}

/* Pass in location of error (first byte position is
   labeled starting at 1, not 0), and the codeword.
*/
void
byte_erasure (int loc, unsigned char dst[], int cwsize, int erasures[]) 
{
  printf("Erasure at loc %d, data %#x\n", loc, dst[loc-1]);
  dst[loc-1] = 0;
}


void test_rsCode2(void){
  unsigned char msg[]= "pi=3.14159265358979";
  unsigned char codeword[256];
  int parityBit[] = {17,13,204,195,220,98,89,28,153,127};
  int k = 0, i = 0;
  int erasures[16];
  int nerasures = 0;
  
  for(i=0;i<=19;i++){
    codeword[i] = msg[i];
  }
  
  printf("codeword = %s", codeword);
  
 codeword[19] = 17;
 codeword[20] = 13;
 codeword[21] = 204;
 codeword[22] = 195;
 codeword[23] = 220;
 codeword[24] = 98;
 codeword[25] = 89;
 codeword[26] = 28;
 codeword[27] = 153;
 codeword[28] = 127;
 
  printf("[%d]", codeword[28]);
  
  byte_err(0x35, 5, codeword);
  printf("Error codeword = %s", codeword);
    // erasures[nerasures++] = ML-3;
  decode_data(codeword, (sizeof (msg) + NPAR));
  
  if (check_syndrome () != 0) {
    correct_errors_erasures (codeword, 
			     ML,
			     nerasures, 
			     erasures);
 
    printf("Corrected codeword: \"%s\"\n", codeword);
  }
}
