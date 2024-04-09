#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  if (!dst) code = 1;
  if (src < 0)
    dst->bits[3] = 0b10000000000000000000000000000000;
  else dst->bits[3] = 0b00000000000000000000000000000000;
  dst->bits[2] = 0b00000000000000000000000000000000;
  dst->bits[1] = 0b00000000000000000000000000000000;
  dst->bits[0] = 0b00000000000000000000000000000000;
  src = abs(src);
  for (int i = 31; i > 0&&src > 0; i--) {
    if (src / (int)pow(2, i) > 0) {
      dst->bits[0] = (dst->bits[0] | 0b00000000000000000000000000000001 << i);
      src -= (int)pow(2, i);
    }
  }
  return code;
}
