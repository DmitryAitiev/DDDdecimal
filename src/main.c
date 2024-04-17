#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal a = {{0x9ab8b17f, 0xec91eb14, 0x3e2129ce, 0x80140000}};
  s21_decimal res;
  int s21_ret = s21_round(a, &res);
  return 0;
}