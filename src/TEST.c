#include <check.h>

#include "s21_decimal.h"

#define TEST_CONVERSION_OK 0
#define TEST_CONVERSION_ERROR 1

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

typedef union test_decimal_bytes {
  s21_decimal d;
  struct {
    uint32_t part0;
    uint32_t part1;
    uint32_t part2;
    uint32_t empty2 : 16;
    uint32_t power : 8;
    uint32_t empty1 : 7;
    uint32_t sign : 1;
  } parts;
} test_decimal_bytes;

int test_decimal_get_sign(s21_decimal value) {
  test_decimal_bytes decimal_bytes;
  decimal_bytes.d = value;
  return decimal_bytes.parts.sign;
}

void test_from_decimal_to_float(s21_decimal decimal, int check) {
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  float_cast_test cast_result;
  cast_result.f = result;

  ck_assert_int_eq(cast_result.int32_bytes, check);
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

void test_from_float_to_decimal(int f, s21_decimal decimal_check) {
  s21_decimal result;

  float_cast_test cast_float;
  cast_float.int32_bytes = f;

  int code = s21_from_float_to_decimal(cast_float.f, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_OK);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

void test_from_decimal_to_int(s21_decimal decimal, int check) {
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

void test_from_int_to_decimal(int number, s21_decimal decimal_check) {
  s21_decimal result;
  int code = s21_from_int_to_decimal(number, &result);
  int sign_check = test_decimal_get_sign(decimal_check);
  int sign_result = test_decimal_get_sign(result);
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}

//void setSign(s21_decimal *value, unsigned int sign);

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_20) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = 100;
  int tmp2 = 99999;
  int res_s21 = 0;
  int res = -99899;
  s21_decimal res1;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(sub_21) {
  s21_decimal dec1;
  s21_decimal dec2;
  int tmp1 = -100;
  int tmp2 = -99999;
  int res_s21 = 0;
  s21_decimal res1;
  int res = 99899;
  s21_from_int_to_decimal(tmp1, &dec1);
  s21_from_int_to_decimal(tmp2, &dec2);
  s21_sub(dec1, dec2, &res1);
  s21_from_decimal_to_int(res1, &res_s21);
  ck_assert_int_eq(res_s21, res);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  set_scale(&val1, 5);
  set_scale(&val2, 3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

//START_TEST(mul_0) {
//  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{2, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_1) {
//  s21_decimal val1 = {{2, 0, 0, 0}};
//  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_2) {
//  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_3) {
//  s21_decimal val1 = {{2, 0, 0, 0}};
//  s21_decimal val2 = {{2, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_4) {
//  s21_decimal val1 = {{8, 0, 0, 0}};
//  s21_decimal val2 = {{2, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_5) {
//  s21_decimal val1 = {{2, 0, 0, 0}};
//  s21_decimal val2 = {{8, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_6) {
//  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{2, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_7) {
//  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{8, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_8) {
//  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_10) {
//  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
//  s21_decimal val2 = {{2, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(mul_11) {
//  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{0, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(div_0) {
//  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{2, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_div(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(div_1) {
//  s21_decimal val1 = {{2, 0, 0, 0}};
//  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_div(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(div_2) {
//  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(0, s21_div(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(div_3) {
//  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
//  s21_decimal val2 = {{0, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(3, s21_div(val1, val2, &res));
//}
//END_TEST
//
//START_TEST(div_4) {
//  s21_decimal val1 = {{2, 0, 0, 0}};
//  s21_decimal val2 = {{0, 0, 0, 0}};
//  s21_decimal res = {{0}};
//  ck_assert_int_eq(3, s21_div(val1, val2, &res));
//}
//END_TEST

START_TEST(s21_is_less_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
    ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
  }
}
END_TEST

START_TEST(s21_is_less_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  setSign(&value_1, 0);
  setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  set_scale(&value_1, 8);
  set_scale(&value_2, 8);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  set_scale(&value_2, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
}
END_TEST

START_TEST(s21_is_less_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
  setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  setSign(&value_1, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_null) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
    ck_assert_int_eq(s21_is_greater(value_2, value_1), 1);
  }
}
END_TEST

START_TEST(s21_is_greater_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  setSign(&value_1, 0);
  setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_greater_two_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  setSign(&value_1, 1);
  setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  }
}
END_TEST

START_TEST(s21_is_greater_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  setSign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  setSign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  setSign(&value_2, 0);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  setSign(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(isEqual_1) {
  s21_decimal a = {{48, 0}}, b = {{48, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(isEqual_2) {
  s21_decimal a = {{1, 1, 0, 0}}, b = {{1, 1, 1, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(s21_not_equal_null) {
  s21_decimal value = {0};
  s21_decimal test = {0};
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 0);
}
END_TEST

//START_TEST(s21_not_equal_normal) {
//  s21_decimal value = {{5}};
//  s21_decimal test = {{6}};
//  int res = s21_is_not_equal(value, test);
//  ck_assert_int_eq(res, 1);
//}
//END_TEST

START_TEST(s21_not_equal_negative) {
  s21_decimal value = {{5}};
  s21_decimal test = {{5}};
  setSign(&value, 1);
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *s21_compare_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_compare_suite");
  tc_core = tcase_create("Compare_Core");

  tcase_add_test(tc_core, s21_is_less_normal);
  tcase_add_test(tc_core, s21_is_less_negative);
  tcase_add_test(tc_core, s21_is_less_pow);

  tcase_add_test(tc_core, s21_is_less_or_equal_normal);
  tcase_add_test(tc_core, s21_is_less_or_equal_with_sign);

  tcase_add_test(tc_core, s21_is_greater_null);
  tcase_add_test(tc_core, s21_is_greater_normal);
  tcase_add_test(tc_core, s21_is_greater_negative);
  tcase_add_test(tc_core, s21_is_greater_two_negative);
  tcase_add_test(tc_core, s21_is_greater_or_equal_normal);
  tcase_add_test(tc_core, s21_is_greater_or_equal_with_sign);
  tcase_add_test(tc_core, s21_one_greater);

  tcase_add_test(tc_core, isEqual_1);
  tcase_add_test(tc_core, isEqual_2);
  tcase_add_test(tc_core, s21_not_equal_null);
  //tcase_add_test(tc_core, s21_not_equal_normal);
  tcase_add_test(tc_core, s21_not_equal_negative);

  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Test for s21_truncate ============

static s21_decimal arr[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}},  // 2172188218.2812812
    {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}},  // -2181821.218210
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},  // 0.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},  // 10000.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},  // -10000.00
    {{0x00000467, 0x0000007A, 0x00000000, 0x00040000}},  // 52398601.1239
    {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  // -523986011239
    {{0x00000467, 0x0000007A, 0x00003215,
      0x00010000}},  // 23650570576955414727997.5
    {{0x00000467, 0x0000007A, 0x00205FF0,
      0x80020000}},  // -391386782621189641642978.31
    {{0x000F4240, 0x00002710, 0x00002710,
      0x80050000}},  // -1844674407800451901.20000
    {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}},  // 14
    {{0x0000000F, 0x00000000, 0x00000000, 0x80000000}},  // -15
    {{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},  // 100000
    {{0x0000000B, 0x00000000, 0x00000000, 0x00010000}},  // 1.1
    {{0x0000000B, 0x00000000, 0x00000000, 0x80010000}},  // -1.1
    {{0x0000000F, 0x00000000, 0x00000000, 0x80010000}},  // -1.5
    {{0x0000000F, 0x00000000, 0x00000000, 0x00010000}},  // 1.5
    {{0x00000086, 0x00000000, 0x00000000, 0x80020000}},  // -1.34
    {{0x00000086, 0x00000000, 0x00000000, 0x00020000}},  // 1.34
    {{0x000006E5, 0x00000000, 0x00000000, 0x00030000}},  // 1.765
    {{0x000006E5, 0x00000000, 0x00000000, 0x80030000}},  // -1.765
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // 2.5
    {{0x00000019, 0x00000000, 0x00000000, 0x80010000}},  // -2.5
    {{0x1FC40A5F, 0xA98FD4BE, 0x00000000,
      0x00020000}},  // 122182182271212611.51
    {{0x1FC40A5D, 0xA98FD4BE, 0x00000000,
      0x00020000}},  // 122182182271212611.49
    {{0x1FC40A5F, 0xA98FD4BE, 0x00000000,
      0x80020000}},  // -122182182271212611.51
    {{0x1FC40A5D, 0xA98FD4BE, 0x00000000,
      0x80020000}},  // -122182182271212611.49
    {{0x075BCD15, 0x00000000, 0x00000000, 0x00030000}},  // 123456.789
    {{0x075BCD15, 0x00000000, 0x00000000, 0x00090000}},  // 0.123456789
    {{0x075BCD15, 0x00000000, 0x00000000, 0x00120000}},  // 0.000000000123456789
    {{0x075BCD15, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000123456789
    {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00060000}},  // 4294.967295
    {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
      0x00050000}},  // 184467440737095.51615
    {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80060000}},  // -4294.967295
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x001C0000}},  // 7.9228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
      0x80050000}},  // -184467440737095.51615
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x801C0000}},  // -7.9228162514264337593543950335
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x8178F63A, 0x00000000, 0x00000000, 0x00000000}},  // 2172188218
    {{0x00214ABD, 0x00000000, 0x00000000, 0x80000000}},  //-2181821
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593543950335
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00002710, 0x00000000, 0x00000000, 0x00000000}},  // 10000
    {{0x00002710, 0x00000000, 0x00000000, 0x80000000}},  //-10000
    {{0x031F8A09, 0x00000000, 0x00000000, 0x00000000}},  // 52398601
    {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  //-523986011239
    {{0xCCCCCD3D, 0x199999A5, 0x00000502,
      0x00000000}},  // 23650570576955414727997
    {{0xBD70A3E2, 0x1EB851EC, 0x000052E1,
      0x80000000}},  //-391386782621189641642978
    {{0xB333333D, 0x19999999, 0x00000000, 0x80000000}},
    //-1844674407800451901
    {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}},  // 14
    {{0x0000000F, 0x00000000, 0x00000000, 0x80000000}},  //-15
    {{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},  // 100000
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
    {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},  //-2
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}},  // 122182182271212611
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}},  // 122182182271212611
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}},  //-122182182271212611
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}},  //-122182182271212611
    {{0x0001E240, 0x00000000, 0x00000000, 0x00000000}},  // 123456
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x000010C6, 0x00000000, 0x00000000, 0x00000000}},  // 4294
    {{0xAC471B47, 0x0000A7C5, 0x00000000, 0x00000000}},  // 184467440737095
    {{0x000010C6, 0x00000000, 0x00000000, 0x80000000}},  //-4294
    {{0x00000007, 0x00000000, 0x00000000, 0x00000000}},  // 7
    {{0xAC471B47, 0x0000A7C5, 0x00000000, 0x80000000}},  //-184467440737095
    {{0x00000007, 0x00000000, 0x00000000, 0x80000000}},  //-7
};

START_TEST(test_s21_truncate) {
  for (size_t i = 0; i < sizeof(arr) / sizeof(s21_decimal); ++i) {
    s21_decimal tmp;
    int ret = s21_truncate(arr[i], &tmp);
    ck_assert_int_eq(tmp.bits[0], result[i].bits[0]);
    ck_assert_int_eq(tmp.bits[1], result[i].bits[1]);
    ck_assert_int_eq(tmp.bits[2], result[i].bits[2]);
    ck_assert_int_eq(tmp.bits[3], result[i].bits[3]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_truncate");
  tc_core = tcase_create("s21_truncate_Core");
  tcase_add_test(tc_core, test_s21_truncate);
  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Tests for s21_round ============

START_TEST(s21_round_0) {
  s21_decimal a = {{0x9ab8b17f, 0xec91eb14, 0x3e2129ce, 0x80140000}};
  s21_decimal res;
  s21_decimal expected = {{0x0b75fc1a, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal a = {{0x30d2fe4f, 0x2343de9f, 0x3e2129d7, 0x00050000}};
  s21_decimal res;
  s21_decimal expected = {{0x6a7e7215, 0x9ba0147d, 0x000028b7, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal a = {{0xc7df0000, 0x4a028ace, 0x4b11543e, 0x00150000}};
  s21_decimal res;
  s21_decimal expected = {{0x01627f45, 0x00000000, 0x00000000, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal a = {{0x57ef0000, 0x2aa64d34, 0x6ef839c0, 0x800a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x974109c0, 0x2fa93d6f, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal a = {{0xc21f0000, 0x84e3bbf7, 0x723bc2fa, 0x00090000}};
  s21_decimal res;
  s21_decimal expected = {{0x2d459980, 0xeaa0fff5, 0x00000001, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal a = {{0x2c4f0000, 0xdf212abb, 0x757f4c34, 0x80080000}};
  s21_decimal res;
  s21_decimal expected = {{0x74082f00, 0xb677ff90, 0x00000013, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal a = {{0x967f0000, 0x395e997e, 0x78c2d56f, 0x00070000}};
  s21_decimal res;
  s21_decimal expected = {{0x6173b600, 0x9a7bfb83, 0x000000ca, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal a = {{0x57e3f000, 0x3a7b1eb0, 0x000100ad, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal a = {{0xf535e9f0, 0x000e5ab9, 0x00000000, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_round");
  tc_core = tcase_create("s21_round_Core");
  tcase_add_test(tc_core, s21_round_0);
  tcase_add_test(tc_core, s21_round_1);
  tcase_add_test(tc_core, s21_round_2);
  tcase_add_test(tc_core, s21_round_3);
  tcase_add_test(tc_core, s21_round_4);
  tcase_add_test(tc_core, s21_round_5);
  tcase_add_test(tc_core, s21_round_6);
  tcase_add_test(tc_core, s21_round_7);
  tcase_add_test(tc_core, s21_round_8);
  suite_add_tcase(s, tc_core);
  return s;
}

// ============ Test for s21_negate ============

START_TEST(test_s21_negate_0) {
  s21_decimal a = {{0x23559a40, 0x00000002, 0x00000000, 0x800a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x23559a40, 0x00000002, 0x00000000, 0x000a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal a = {{0xd6b52360, 0x00000001, 0x00000000, 0x800a0000}};
  s21_decimal res;
  s21_decimal expected = {{0xd6b52360, 0x00000001, 0x00000000, 0x000a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal a = {{0x23559a40, 0x00000002, 0x00000000, 0x000a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x23559a40, 0x00000002, 0x00000000, 0x800a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_negate");
  tc_core = tcase_create("s21negate_Core");
  tcase_add_test(tc_core, test_s21_negate_0);
  tcase_add_test(tc_core, test_s21_negate_1);
  tcase_add_test(tc_core, test_s21_negate_2);
  suite_add_tcase(s, tc_core);
  return s;
}

// ============ Test for s21_floor ============

START_TEST(s21_floor_1) {
  s21_decimal a = {{0xff57162f, 0x174ff0e4, 0x3e2129cb, 0x001b0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000013, 0x00000000, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal a = {{0xb8bdf40f, 0x911be896, 0x3e2129d0, 0x00110000}};
  s21_decimal res;
  s21_decimal expected = {{0xc4e0c68d, 0x0000002c, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal a = {{0xd6c3369f, 0x35a5e618, 0x3e2129d2, 0x800e0000}};
  s21_decimal res;
  s21_decimal expected = {{0x0e0c3971, 0x0000aee1, 0x00000000, 0x80000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal a = {{0x44ff0000, 0x67732363, 0x5ea68b9c, 0x000f0000}};
  s21_decimal res;
  s21_decimal expected = {{0x4accef76, 0x00001aa4, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal a = {{0x57e3f000, 0x3a7b1eb0, 0x000100ad, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal a = {{0xc21f0000, 0x84e3bbf7, 0x723bc2fa, 0x00090000}};
  s21_decimal res;
  s21_decimal expected = {{0x2d459980, 0xeaa0fff5, 0x00000001, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal a = {{0x967f0000, 0x395e997e, 0x78c2d56f, 0x00070000}};
  s21_decimal res;
  s21_decimal expected = {{0x6173b600, 0x9a7bfb83, 0x000000ca, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal a = {{0xd1281800, 0x588f9004, 0x00001787, 0x001c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_from_decimal_to_float_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = 1870659584;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int check = -276824064;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  int check = 1842138317;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  int check = -305345331;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok5) {
  // 20995463066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x0}};
  int check = 1854385684;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok6) {
  // -20995463066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80000000}};
  int check = -293097964;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok7) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  int check = 1814288138;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok8) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  int check = -333195510;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok9) {
  // 2099546306628004946228914683.9
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x10000}};
  int check = 1826166407;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok10) {
  // -2099546306628004946228914683.9
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80010000}};
  int check = -321317241;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_float_to_decimal_ok1) {
  // 2.28401628E-19
  int f = 545706772;
  // 0.0000000000000000002284016
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2) {
  // -2.28401628E-19
  int f = -1601776876;
  // -0.0000000000000000002284016
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x80190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok3) {
  // 5.92141241E+23
  int f = 1727711253;
  // 592141200000000000000000
  s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok4) {
  // -5.92141241E+23
  int f = -419772395;
  // -592141200000000000000000
  s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok5) {
  // 2.1349025E-18
  int f = 572360491;
  // 0.000000000000000002134902
  s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok6) {
  // -2.1349025E-18
  int f = -1575123157;
  // -0.000000000000000002134902
  s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x80180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok7) {
  // 2.38582807E-08
  int f = 852291818;
  // 0.00000002385828
  s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0xE0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok8) {
  // -2.38582807E-08
  int f = -1295191830;
  // -0.00000002385828
  s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0x800E0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok9) {
  // 7.91617864E+11
  int f = 1396199450;
  // 791617900000
  s21_decimal decimal_check = {{0x501A8DE0, 0xB8, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok10) {
  // -7.91617864E+11
  int f = -751284198;
  // -791617900000
  s21_decimal decimal_check = {{0x501A8DE0, 0xB8, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_decimal_to_int_ok1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int check = 792281625;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok2) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  int check = -792281625;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok3) {
  // 79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
  int check = 79228162;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok4) {
  // -79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
  int check = -79228162;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok5) {
  // 7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
  int check = 7922816;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok6) {
  // -7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
  int check = -7922816;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok7) {
  // 792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
  int check = 792281;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok8) {
  // -792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
  int check = -792281;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok9) {
  // 79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
  int check = 79228;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_decimal_to_int_ok10) {
  // -79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
  int check = -79228;

  test_from_decimal_to_int(decimal, check);
}

START_TEST(test_from_int_to_decimal_ok1) {
  int number = -2147483648;
  // Converted the Int32 value -2147483648 to the Decimal value -2147483648.
  s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok2) {
  int number = -2147483647;
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal decimal_check = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok3) {
  int number = -214748364;
  // Converted the Int32 value -214748364 to the Decimal value -214748364.
  s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok4) {
  int number = -214748;
  // Converted the Int32 value -214748 to the Decimal value -214748.
  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok5) {
  int number = -1000;
  // Converted the Int32 value -1000 to the Decimal value -1000.
  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80000000}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok6) {
  int number = -1;
  // Converted the Int32 value -1 to the Decimal value -1.
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok7) {
  int number = 0;
  // Converted the Int32 value 0 to the Decimal value 0.
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok8) {
  int number = 1;
  // Converted the Int32 value 1 to the Decimal value 1.
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok9) {
  int number = 1000;
  // Converted the Int32 value 1000 to the Decimal value 1000.
  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x0}};

  test_from_int_to_decimal(number, decimal_check);
}

START_TEST(test_from_int_to_decimal_ok10) {
  int number = 214748;
  // Converted the Int32 value 214748 to the Decimal value 214748.
  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

  test_from_int_to_decimal(number, decimal_check);
}

Suite *s21_floor_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_floor");
  tc_core = tcase_create("s21_floor_Core");
  tcase_add_test(tc_core, s21_floor_1);
  tcase_add_test(tc_core, s21_floor_2);
  tcase_add_test(tc_core, s21_floor_3);
  tcase_add_test(tc_core, s21_floor_4);
  tcase_add_test(tc_core, s21_floor_5);
  tcase_add_test(tc_core, s21_floor_6);
  tcase_add_test(tc_core, s21_floor_7);
  tcase_add_test(tc_core, s21_floor_8);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, sub_0);  // s21_sub
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_12);
  tcase_add_test(tc1_1, sub_13);
  tcase_add_test(tc1_1, sub_15);
  tcase_add_test(tc1_1, sub_16);
  tcase_add_test(tc1_1, sub_17);
  tcase_add_test(tc1_1, sub_18);
  tcase_add_test(tc1_1, sub_19);
  tcase_add_test(tc1_1, sub_20);
  tcase_add_test(tc1_1, sub_21);
  tcase_add_test(tc1_1, add_0);  // s21_add
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
 // tcase_add_test(tc1_1, mul_0);  // s21_mul
 // tcase_add_test(tc1_1, mul_1);
 // tcase_add_test(tc1_1, mul_2);
 // tcase_add_test(tc1_1, mul_3);
 // tcase_add_test(tc1_1, mul_4);
 // tcase_add_test(tc1_1, mul_5);
 // tcase_add_test(tc1_1, mul_6);
 // tcase_add_test(tc1_1, mul_7);
 // tcase_add_test(tc1_1, mul_8);
 // tcase_add_test(tc1_1, mul_10);
 // tcase_add_test(tc1_1, mul_11);
 // tcase_add_test(tc1_1, div_0);  // s21_div
 // tcase_add_test(tc1_1, div_1);
 // tcase_add_test(tc1_1, div_2);
 // tcase_add_test(tc1_1, div_3);
 // tcase_add_test(tc1_1, div_4);

  tcase_add_test(tc1_1, test_from_decimal_to_float_ok1);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok2);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok3);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok4);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok5);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok6);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok7);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok8);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok9);
  tcase_add_test(tc1_1, test_from_decimal_to_float_ok10);

  tcase_add_test(tc1_1, test_from_float_to_decimal_ok1);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok2);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok3);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok4);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok5);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok6);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok7);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok8);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok9);
  tcase_add_test(tc1_1, test_from_float_to_decimal_ok10);

  tcase_add_test(tc1_1, test_from_decimal_to_int_ok1);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok2);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok3);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok4);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok5);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok6);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok7);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok8);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok9);
  tcase_add_test(tc1_1, test_from_decimal_to_int_ok10);

  tcase_add_test(tc1_1, test_from_int_to_decimal_ok1);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok2);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok3);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok4);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok5);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok6);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok7);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok8);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok9);
  tcase_add_test(tc1_1, test_from_int_to_decimal_ok10);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  Suite *decimal_tests[] = {s21_compare_suite(),  s21_floor_suite(),
                            s21_round_suite(),    s21_negate_suite(),
                            s21_truncate_suite(), NULL};
  for (int i = 0; decimal_tests[i] != NULL; i++) {
    SRunner *srunner;
    srunner = srunner_create(decimal_tests[i]);
    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_NORMAL);
    nf += srunner_ntests_failed(srunner);
    srunner_free(srunner);
  }

  return nf == 0 ? 0 : 1;
}
