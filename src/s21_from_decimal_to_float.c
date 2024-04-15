#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst){
  int code =0, scale=get_scale(src);
double result = 0;

  result += src.bits[0];

for(int i = 63; i >= 32; i--){
  if (_get_bit_int(src.bits[1], i))
 result += pow(2, i);
}

for(int i = 95; i >= 64; i--){
  if (_get_bit_int(src.bits[2], i))
 result += pow(2, i);
}

float res=(float)result/pow(10,scale);
if (get_sign(src)) res=res*(-1);
*dst = res;
return code;
}

