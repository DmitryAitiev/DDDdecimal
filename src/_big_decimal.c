#include "s21_decimal.h"

int s21_decimal_is_zero(s21_decimal dec) {
  int res = 0;
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) {
    res = 1;
  }
  return res;
}
