#include <stdio.h>

#include "s21_decimal.h"

typedef union float_cast_test {
  float f;
  struct {
    uint32_t mantisa : 23;
    uint32_t exponent : 8;
    uint32_t sign : 1;
  } parts;
  uint32_t bytes;
  int int32_bytes;
} float_cast_test;

void test_from_decimal_to_float(s21_decimal decimal, int check) {
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  float_cast_test cast_result;
  cast_result.f = result;

  // ck_assert_int_eq(cast_result.int32_bytes, check);
  // ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

int main() {
  float result = 0;
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x10000}};
  int check = -321317241;
  test_from_decimal_to_float(decimal, check);
  return 0;
}