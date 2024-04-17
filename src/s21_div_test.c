#include "suits.h"

START_TEST(s21_div_test_1) {
  s21_decimal val1 = {{411601037, 3190096481, 685266662,
                       0x001C0000}};  // sign bit= 0 exponent= -28
  // 1.2640938749860586450804312205
  s21_decimal val2 = {{2, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
  // 2
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2353284166);
  ck_assert_int_eq(res.bits[1], 1595048240);
  ck_assert_int_eq(res.bits[2], 342633331);
  ck_assert_uint_eq(res.bits[3], 1835008);  // sign bit= 0 exponent= -28
  // 0.6320469374930293225402156102
}
END_TEST

START_TEST(s21_div_test_14) {
  s21_decimal number1 = {{864192, 0, 0, 0x00030000}};
  s21_decimal number2 = {{7, 0, 0, 0x00000000}};
  s21_decimal res;

  ck_assert_int_eq(0, s21_div(number1, number2, &res));
  ck_assert_int_eq(res.bits[0], 123456);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 196608);
}
END_TEST

START_TEST(s21_div_test_2) {
  s21_decimal val1 = {{15, 15, 15, 0x000F0000}};
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 15);
  ck_assert_int_eq(res.bits[1], 15);
  ck_assert_int_eq(res.bits[2], 15);
  ck_assert_int_eq(res.bits[3], 1048576);
}
END_TEST

START_TEST(s21_div_test_3) {
  s21_decimal val1 = {{123, 456, 789, 0x00040000}};
  s21_decimal val2 = {{1, 1, 1, 0x00050000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 405681253);
  ck_assert_int_eq(res.bits[1], 150366383);
  ck_assert_int_eq(res.bits[2], 4277177570);
  ck_assert_int_eq(res.bits[3], 1638400);
}
END_TEST

START_TEST(s21_div_test_4) {
  s21_decimal val1 = {{2, 0, 0, 0x00000000}};
  s21_decimal val2 = {{5, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2684354560);
  ck_assert_int_eq(res.bits[1], 2135032051);
  ck_assert_int_eq(res.bits[2], 216840434);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_div_test_5) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x001C0000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_div_test_6) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_7) {
  s21_decimal val1 = {{123, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x000A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1639353344);
  ck_assert_int_eq(res.bits[1], 286);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_div_test_8) {
  s21_decimal val1 = {{123, 123, 123, 0x00050000}};
  s21_decimal val2 = {{1, 2, 3, 0x000A0000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 3942814950);
  ck_assert_int_eq(res.bits[1], 3297597181);
  ck_assert_int_eq(res.bits[2], 2222614453);
  ck_assert_int_eq(res.bits[3], 1441792);
}
END_TEST

START_TEST(s21_div_test_9) {
  s21_decimal val1 = {{1234567890, 0, 0, 0x00050000}};
  s21_decimal val2 = {{0, 0, 0, 0x800A0000}};
  s21_decimal res;
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(s21_div_test_10) {
  s21_decimal val1 = {{387420489, 999999999, 123456789, 0x000E0000}};
  s21_decimal val2 = {{987654321, 666666666, 888888888, 0x80190000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 2966737934);
  ck_assert_int_eq(res.bits[1], 2263411014);
  ck_assert_int_eq(res.bits[2], 752918170);
  ck_assert_int_eq(res.bits[3], 2148663296);
}
END_TEST

START_TEST(s21_div_test_11) {
  s21_decimal val1 = {{123456, 0, 0, 0x00040000}};
  s21_decimal val2 = {{123, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1964161873);
  ck_assert_int_eq(res.bits[1], 2944270678);
  ck_assert_int_eq(res.bits[2], 54411082);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_div_test_12) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};
  s21_decimal val2 = {{3, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 89478485);
  ck_assert_int_eq(res.bits[1], 347537611);
  ck_assert_int_eq(res.bits[2], 180700362);
  ck_assert_int_eq(res.bits[3], 1835008);
}
END_TEST

START_TEST(s21_div_test_13) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, 0);
}
END_TEST

// START_TEST(s21_div_test_X) {
//   s21_decimal val1 = {{2, 0, 0, 0x00000000}};  // sign bit= 0 exponent= 0
//   // 2
//   s21_decimal val2 = {{411601037, 3190096481, 685266662,
//                        0x001C0000}};  // sign bit= 0 exponent= -28
//   // 1.2640938749860586450804312205
//   s21_decimal res;
//   ck_assert_int_eq(0, s21_div(val1, val2, &res));
//   ck_assert_int_eq(res.bits[0], 1093040346);
//   ck_assert_int_eq(res.bits[1], 1772880886);
//   ck_assert_int_eq(res.bits[2], 85769118);
//   ck_assert_uint_eq(res.bits[3], 1769472);  // sign bit= 0 exponent= -27
//   // 1.582160976788260656446339290
// }
// END_TEST

Suite *s21_div_suite(void) {
  Suite *s = suite_create("\033[34m \033[46m DIV TESTS \033[0m");
  TCase *tc = tcase_create("div_tc");

  tcase_add_test(tc, s21_div_test_1);
  tcase_add_test(tc, s21_div_test_2);
  tcase_add_test(tc, s21_div_test_3);
  tcase_add_test(tc, s21_div_test_4);
  tcase_add_test(tc, s21_div_test_5);
  tcase_add_test(tc, s21_div_test_6);
  tcase_add_test(tc, s21_div_test_7);
  tcase_add_test(tc, s21_div_test_8);
  tcase_add_test(tc, s21_div_test_9);
  tcase_add_test(tc, s21_div_test_10);
  tcase_add_test(tc, s21_div_test_11);
  tcase_add_test(tc, s21_div_test_12);
  tcase_add_test(tc, s21_div_test_13);
  tcase_add_test(tc, s21_div_test_14);

  suite_add_tcase(s, tc);

  return s;
}