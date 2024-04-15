#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst){
int code=0;
if (!dst || fabs(src) > 79228162514264337593543950335.0) {
    code = 1;
  }
nullify(dst);
if(src < 0)
  dst->bits[3] = 0b10000000000001100000000000000000;
else dst->bits[3] = 0b00000000000001100000000000000000;
float FP, lp;
src=fabs(src);
lp=modff(src, &FP);
long double fp=(long double)FP, result= fp*pow(10,6)+lp*pow(10,6);

for(int i = 95; i >= 64; i--){
  if (result/ pow(2,i) > 1){
  dst->bits[2] = dst->bits[2] |  0b00000000000000000000000000000001 << i;
  result -= pow(2, i);
  }
}

for(int i = 63; i >= 32; i--){
  if (result/ pow(2,i) > 1){
  dst->bits[1] = dst->bits[1] |  0b00000000000000000000000000000001 << i;
  result -= pow(2, i);
  }
}

for(int i = 31; i >= 0; i--){
  if (result/ pow(2,i) > 1){
  dst->bits[0] = dst->bits[0] |  0b00000000000000000000000000000001 << i;
  result -= pow(2, i); 
  }
}
return code;
}