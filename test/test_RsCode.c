#include "unity.h"
#include "RsCode.h"
#include "rs.c"

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

  // byte_err(0x23, 17, codeword);
  // byte_err(0x34, 19, codeword);


  printf("with some errors: \"%s\"\n", codeword);

  /* We need to indicate the position of the erasures.  Eraseure
     positions are indexed (1 based) from the end of the message... */

  // erasures[nerasures++] = ML-17;
  // erasures[nerasures++] = ML-19;

 
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
  // unsigned char msg[32]= "pi=3.14159265358979";
  
  // unsigned char msg [] = {65,55,6,147,211,50,227,19,67,19,83,147,35,99,83,51,83,131,147,115,\
                  // 144,236,17,236, 17, 236, 17, 236, 17, 236, 17, 236, 17, 236};
  unsigned char msg [] = {8,6,8,1,2,4,15,9,9};
                  
  unsigned char codeword[256];

  int k = 0, i = 0;
  int erasures[16];
  int nerasures = 0;
  


  // printf("codeword = %s", codeword);
  printf("\nsizeof = %d", sizeof(msg));
  
  printf("\n%d", msg[0]);
  printf("\n%c", 112);
  encode_data(msg, sizeof(msg), codeword);
  print_parity();
  // codeword[20] = 26;  //00011010
  // codeword[21] = 228; //11100100
  // codeword[22] = 4;   //00000100 
  // codeword[23] = 196; //11000100
  // codeword[24] = 106; //01101010
  // codeword[25] = 21;  //00010101
  // codeword[26] = 8;   //00001000
  // codeword[27] = 17;  //00010001
  // codeword[28] = 191; //10111111
  // codeword[29] = 81;  //01010001

  // codeword[19] = 17;   //00010001
  // codeword[20] = 13;   //00001101
  // codeword[21] = 204;  //11001100
  // codeword[22] = 195;  //11000011
  // codeword[23] = 220;  //11011100
  // codeword[24] = 98;   //01100010
  // codeword[25] = 89;   //01011001
  // codeword[26] = 28;   //00011100
  // codeword[27] = 153;  //10011001
  // codeword[28] = 127;  //01111111
 
  initialize_ecc ();
  printf("[%d]", codeword[28]);
  
  byte_err(0x35, 5, codeword);
  printf("Error codeword = %s\n", codeword);
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

void test_rs_decode(void){
  register int i;

/* generate the Galois Field GF(2**mm) */
  generate_gf() ;
  printf("Look-up tables for GF(2**%2d)\n",mm) ;
  printf("  i   alpha_to[i]  index_of[i]\n") ;
  for (i=0; i<=nn; i++)
   printf("%3d      %3d          %3d\n",i,alpha_to[i],index_of[i]) ;
  printf("\n\n") ;

/* compute the generator polynomial for this RS code */
  gen_poly() ;


/* for known data, stick a few numbers into a zero codeword. Data is in
   polynomial form.
*/
for  (i=0; i<kk; i++)   data[i] = 0 ;

/* for example, say we transmit the following message (nothing special!) */
data[0] = 8 ;
data[1] = 6 ;
data[2] = 8 ;
data[3] = 1 ;
data[4] = 2 ;
data[5] = 4 ;
data[6] = 15 ;
data[7] = 9 ;
data[8] = 9 ;

/* encode data[] to produce parity in bb[].  Data input and parity output
   is in polynomial form
*/
  encode_rs() ;

/* put the transmitted codeword, made up of data plus parity, in recd[] */
  for (i=0; i<nn-kk; i++)  recd[i] = bb[i] ;
  for (i=0; i<kk; i++) recd[i+nn-kk] = data[i] ;
  
 for (i=0; i<nn-kk; i++) 
   printf("%d,", bb[i]);

/* if you want to test the program, corrupt some of the elements of recd[]
   here. This can also be done easily in a debugger. */
/* Again, lets say that a middle element is changed */
  data[nn-nn/2] = 3 ;


  for (i=0; i<nn; i++)
     recd[i] = index_of[recd[i]] ;          /* put recd[i] into index form */

/* decode recv[] */
  decode_rs() ;         /* recd[] is returned in polynomial form */

/* print out the relevant stuff - initial and decoded {parity and message} */
  printf("Results for Reed-Solomon code (n=%3d, k=%3d, t= %3d)\n\n",nn,kk,tt) ;
  printf("  i  data[i]   recd[i](decoded)   (data, recd in polynomial form)\n");
  for (i=0; i<nn-kk; i++)
    printf("%3d    %3d      %3d\n",i, bb[i], recd[i]) ;
  for (i=nn-kk; i<nn; i++)
    printf("%3d    %3d      %3d\n",i, data[i-nn+kk], recd[i]) ;
}