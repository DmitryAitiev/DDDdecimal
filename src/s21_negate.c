#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    value.bits[3] = value.bits[3] ^ ((unsigned int)1 << 31);  // * -1
    *result = value;
  } else {
    error = 1;
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result) {
    uint64_t rem = 0;  //остаток
    int scale = get_scale(value);

    while (scale > 0) {
      for (int i = 2; i >= 0; --i) {
        uint64_t num = value.bits[i];
        num += rem << 32;
        rem = num % 10;
        num /= 10;
        value.bits[i] = num;
      }
      scale--;
      rem = 0;
    }
    set_scale(&value, 0);
    *result = value;
  } else {
    err = 1;
  }
  return err;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    s21_decimal trunc_value = {0};
    s21_decimal fraction = {0};
    s21_decimal zero_dec = {0};
    s21_truncate(value, &trunc_value);  // убираем дробную часть
    s21_sub(value, trunc_value, &fraction);  // находим дробную часть
    if (value.bits[3] >> 31) {               // если -
      s21_negate(fraction, &fraction);            // ; -1
      if (!s21_is_greater(fraction, zero_dec)) {  // если < 0
        int_add_decimal(
            trunc_value, -1,
            &trunc_value);  // отнимаем -1 - округление в сторону -INF
      }
    }
    *result = trunc_value;
  } else {
    error = 1;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, znak = get_sign(value), scale = get_exp(value);
  int res = 0;
  unsigned long long drob = 0;
  if (result == NULL) {
    error = 1;
  } else {
    s21_decimal buf = {{}};
    if (znak) set_bit(&buf.bits[3], 31, 0);
    s21_truncate(value, &buf);

    //if ((scale) && ((get_bit(0, scale)) >= 5)) res = 1;
    if (scale) {
        for(int i = scale - 1; i >=0; i--){
            if (value.bits[0] & 0b00000000000000000000000000000001 << i)
                drob += (int)pow(2, i);
        }
    }
    if (drob%((int)pow(10, scale)) >= 5) res = 1;
    if (res) add_one(&buf);
    if (znak) set_bit(&buf.bits[3], 31, 1);

    *result = buf;
   
}
