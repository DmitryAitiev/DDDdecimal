#include "s21_decimal.h"

void _bank_rounding(s21_big_decimal* big, s21_decimal* decimal, int mod,
                    int* scale, unsigned int sign) {
  s21_big_decimal one;
  mine_from_int_to_decimalb(1, &one);
  if ((mod == 5 && get_bit_valueb(*big, 0)) || mod > 5) {
    myaddb(*big, one, big);
  }
  if (countLastBitbig(*big) > 95 && (*scale) > 0) {
    mysubb(*big, one , big);
    mod = div_by_tenb(big);
    (*scale)--;
    _bank_rounding(big, decimal, mod, scale, sign);
  }
  mybig_to_decimal(*big, decimal, *scale, sign);
}


