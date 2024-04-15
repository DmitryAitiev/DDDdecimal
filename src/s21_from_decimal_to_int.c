#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_truncate(src, &src);
  int code = 0;
  int result = 0;
  if (src.bits[1] > 0 || src.bits[2] > 0 || src.bits[0] > 2147483647) {
    code = 1;
  }
  int sign = get_sign(src);
  for (int i = 0; i < 31; i++) {
    if (src.bits[0] & 0b00000000000000000000000000000001 << i)
      result += (int)pow(2, i);
  }
  if(sign)
    *dst = -1*result;
  else *dst = result;
  return code;
}
