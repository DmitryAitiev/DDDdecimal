#include "s21_decimal.h"

int s21_decimal_is_zero(s21_decimal dec) {
  
  int is_zero = 1;
  if (dec.bits[3] || dec.bits[2] || dec.bits[1] || dec.bits[0])
    is_zero = 0;
  return is_zero;
}
