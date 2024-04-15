#include <stdio.h>

#include "s21_decimal.h"

int main() {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
  int check = -7922816;
  int result = -1;
  int code = s21_from_decimal_to_int(decimal, &result);
  return 0;
}