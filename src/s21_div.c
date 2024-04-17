#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK, sign = (get_sign(value_1) + get_sign(value_2)) % 2,
      to_long = OK;
  s21_decimal temp = {{0}};
  s21_big_decimal a, b, c, d, temp2 = {{0}}, dva = {{0, 0, 0, 0, 0, 2, 0}},
                           nuli = {{0}};
  s21_big_decimal des = {{0, 0, 0, 0, 0, 10, 0}};
  my_decimal_to_big(value_1, &a);
  my_decimal_to_big(value_2, &b);
  int nol1 = zeroBigDecimal(a), nol2 = zeroBigDecimal(b);
  if (nol2 == 0) return 3;
  if (nol1 == 0) {
    memcpy(result, &temp, 4 * sizeof(int));
    return res;
  }
  my_decimal_to_big(temp, &c);
  int scale = get_scale(value_1) - get_scale(value_2);
  memcpy(&temp2, &a, 6 * sizeof(int));
  while (to_long == OK) {
    memcpy(&a, &temp2, 6 * sizeof(int));
    to_long = s21_umn_bit(temp2, des, &temp2);
    scale++;
  }
  scale--;
  s21_del_bit(a, b, &c, &d);
  s21_umn_bit(d, dva, &d);
  lset_sign(&c, sign);
  to_norm(&c, &scale);
  if (scale < 0) res = 1 + sign;
  if (res == OK) {
    min_scale(&c, &scale);
    from_long_dec(c, result);
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return res;
}


int s21_del_bit(s21_big_decimal a, s21_big_decimal b, s21_big_decimal *result,
                s21_big_decimal *ostatok) {
  int res = OK, len_a = lget_len(a), len_b = lget_len(b), bit = 0;
  s21_big_decimal new_a = {{0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal temp_res = {{0, 0, 0, 0, 0, 0, 0}};
  lget_new_dec(a, &new_a, len_b);
  for (unsigned long i = 6 * 8 * sizeof(int) - len_a + len_b;
       i <= 6 * 8 * sizeof(int); i++) {
    if (mem_dec(new_a, b) >= 0) {
      bit = 1;
      s21_minus_bit(new_a, b, &new_a);
    } else {
      bit = 0;
    }
    lsdvig_vlevo_it(&temp_res);
    lset_bit(&temp_res, 6 * 8 * sizeof(int) - 1, bit);
    if ((unsigned long)i < 6 * 8 * sizeof(int)) {
      lsdvig_vlevo_it(&new_a);
      lset_bit(&new_a, 6 * 8 * sizeof(int) - 1, lget_bit(a, i));
    }
  }
  memcpy(result, &temp_res, 6 * sizeof(int));
  memcpy(ostatok, &new_a, 6 * sizeof(int));
  return res;
}
