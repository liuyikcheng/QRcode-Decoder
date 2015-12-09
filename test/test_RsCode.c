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
  
  int data[] = {13,45,789,332};
  int eras_pos[] = {1,2};
  int a;
  
	a = eras_dec_rs(data, eras_pos, 2);
  
  
  
  printf("%d", a);
}
