#include "unity.h"
#include "RsCode.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_rsCode(void)
{
  init_rs();
  generate_gf();
  
  gen_poly();	
  
  dtype data[6] = {'A','C','D','E'};
  // int eras_pos[] = {1,2};
  int a;
  
	a = encode_rs(data, &data[3]);
  
  
  
  // printf("%d", a);
}
