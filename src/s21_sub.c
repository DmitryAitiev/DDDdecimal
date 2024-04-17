#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  int sign1 = extractBitSign(value_1);
  int sign2 = extractBitSign(value_2);
  unsigned int sign = 0;
  nullify(result);
  s21_big_decimal big1, big2, resbig, buffer;
  nullifyb(&big1);
  nullifyb(&big2);
  nullifyb(&resbig);
  nullifyb(&buffer);
  int scale = normalize(value_1, value_2, &big1, &big2);
  if (sign1 == sign2) {
    sign = (unsigned int)sign1;
    if ((tsuboika_is_greater(value_2, value_1))) {
      buffer = big1;
      big1 = big2;
      big2 = buffer;
      sign ^= 1u;
      mysubb(big1, big2, &resbig);
      mybig_to_decimal(resbig, result, scale, sign);
    }

    else {
      mysubb(big1, big2, &resbig);
      if (tsuboika_is_equal(value_1, value_2)) sign = 0;
      mybig_to_decimal(resbig, result, scale, sign);
    }
  }
  if (sign1 > sign2) {
    setSign(&value_2, 1);
    error = myaddnormalize(value_2, value_1, result);
    return error;
  }
  if (sign2 > sign1) {
    setSign(&value_2, 0);

    error = myaddnormalize(value_1, value_2, result);

    return error;
  }
  return error;
}
