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
  int error = 0, znak = get_sign(value), scale = get_scale(value);
  int res = 0, count = 0;
  unsigned long long drob = 0;
  if (result == NULL) {
    error = 1;
  } else {
    s21_decimal buf = {{}};
    s21_truncate(value, &buf);
    //if (scale) {
    //  for (int i = scale; i >= 0; i--) {
    //    if (value.bits[0] & 0b00000000000000000000000000000001 << i)
    //      drob += (int)pow(2, i);
    //  }
    //}
    if(scale){
      int i = 0, j = 0;
      while (count != scale){
        if(j <= 31){
        if (value.bits[0] & 0b00000000000000000000000000000001 << j){
          drob += (int)pow(2, j);
          i++;
          count ++;
        }
        j++;
        }
        if (j <= 63 && j >= 32){
          if (value.bits[1] & 0b00000000000000000000000000000001 << (j - 32)){
          drob += (int)pow(2, j);
          i++;
          count ++;
        }
        j++;
        }
        if (j <= 95 && j >= 64){
          if (value.bits[2] & 0b00000000000000000000000000000001 << (j - 64)){
          drob += (int)pow(2, j);
          i++;
          count ++;
        }
        j++;
        }
      }
    }
    if (drob % ((int)pow(10, scale)) >= 5*pow(10, scale-1)) res = 1;
    if (res) add_one(&buf);
    if (znak) setSign(&buf, 1);

    *result = buf;
  }

  return error;
}
