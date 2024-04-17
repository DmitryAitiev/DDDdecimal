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
    uint64_t ostatok = 0;
    int scale = get_scale(value);
    while (scale > 0) {
      for (int i = 2; i >= 0; --i) {
        uint64_t num = value.bits[i];
        num += ostatok << 32;
        ostatok = num % 10;
        num /= 10;
        value.bits[i] = num;
      }
      scale--;
      ostatok = 0;
    }
    set_scale(&value, 0);
    *result = value;
  } else
    err = 1;
  return err;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result == NULL) {
    error = 1;
  } else {
    s21_decimal buf = {{}};
    s21_truncate(value, &buf);

    if (get_sign(value) && !s21_is_equal(value, buf)) {
      set_bit_int(&buf.bits[3], 31, 0);
      add_one(&buf);
      set_bit_int(&buf.bits[3], 31, 1);
    }
    *result = buf;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0, is_signed = 0;
  s21_decimal buf = {{}}, copy_value = value;
  if (result == NULL) {
    error = 1;
  } else {
    for (int i = 0; i < get_scale(value) - 1; i++) {
      division_by_ten(copy_value, &buf);
      copy_value = buf;
      nullify(&buf);
    }
    if (get_sign(value)) {
      set_bit_int(&value.bits[3], 31, 0);
      is_signed = 1;
    }
    if (rem_div_by_ten(copy_value) < 5) {
      s21_floor(value, &buf);
    } else {
      s21_truncate(value, &buf);
      if (get_scale(value)) add_one(&buf);
    }
    *result = buf;
    if (is_signed) setSign(result, 1);
    if (!result->bits[0] && !result->bits[1] && !result->bits[2] && !is_signed)
      result->bits[3] = 0;
    else if (is_signed){
      result->bits[3] = 0;
      setSign(result, 1);
    }
  }
  return error;
}