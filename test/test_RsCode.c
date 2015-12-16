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
  // char codeword[] = "ABC 123456789";
  
  // byte_err(0x35, 3, codeword);
  char codeword[256];
  // int erasures[] = {0, 7, 190, 217, 202, 136, 167};
  // int nerasures = 0;
  // erasures[nerasures++] = ML-17;
  // erasures[nerasures++] = ML-19;
  // #define ML (sizeof (codeword) + NPAR)
  // decode_data(codeword, ML);
  // correct_errors_erasures (codeword, 
			     // ML,
			     // nerasures, 
			     // erasures);
           
           // printf("%s", codeword);
}
