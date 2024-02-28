#include "s21_decimal.h"

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  if (!s21_decimal_is_zero(dec1) && !s21_decimal_is_zero(dec2)) {
    if (get_bit(dec1, 127) < get_bit(dec2, 127)) {
      res = 1;
    } else if (get_bit(dec1, 127) > get_bit(dec2, 127)) {
      res = 0;
    } else {
      normalization(&dec1, &dec2);
      for (int i = 95; i >= 0; --i) {
        if (get_bit(dec1, i) > get_bit(dec2, i)) {
          if (!get_bit(dec1, 127)) {
            res = 1;
          }
          break;
        } else if (get_bit(dec1, i) < get_bit(dec2, i)) {
          if (get_bit(dec1, 127)) {
            res = 1;
          }
          break;
        }
      }
    }
  }
  return res;
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2) ? 0 : 1);
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_less(dec1, dec2) ? 1 : 0);
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2) ? 1 : 0);
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  normalization(&dec1, &dec2);
  if (dec1.bits[0] == dec2.bits[0] && dec1.bits[1] == dec2.bits[1] &&
      dec1.bits[2] == dec2.bits[2] && dec1.bits[3] == dec2.bits[3]) {
    res = 1;
  }
  return res;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2) {
  return !s21_is_equal(dec1, dec2);
}
