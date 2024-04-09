#include "s21_decimal.h"

int s21_mul(s21_decimal val1, s21_decimal val2,
                        s21_decimal* result) {
  int error = 0;
  int sign = 0;
  if (get_sign(val1) == get_sign(val2)) {
    sign = 0;
  } else {
    sign = 1;
  }
  int scale1 = get_scale(val1);
  int scale2 = get_scale(val2);
  // if(scale1>28||scale2>28)return
  int scale = scale1 + scale2;
  s21_decimal add_shift;
  s21_big_decimal big1, big2, resultbig;

  nullify(&add_shift);
  nullify(result);
  nullifyb(&big1);
  nullifyb(&big2);
  nullifyb(&resultbig);
  if (!s21_decimal_is_zero(val1) && !s21_decimal_is_zero(val2)) {
    big1.bits[0] = val1.bits[0];
    big1.bits[1] = val1.bits[1];
    big1.bits[2] = val1.bits[2];
    big2.bits[0] = val2.bits[0];
    big2.bits[1] = val2.bits[1];
    big2.bits[2] = val2.bits[2];

    for (int i = 0; i < 96; i++) {
      if (getBigBit(big2, i)) {
        myaddb(resultbig, big1, &resultbig);
      }

      myshiftleft(&big1, 1);
    }

    error = mybig_to_decimal(resultbig, result, scale, sign);
  }
  return error;
}