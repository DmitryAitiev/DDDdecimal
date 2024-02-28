#include "s21_decimal.h"

s21_decimal_alt _convert_std_to_alt(s21_decimal std) {
  s21_decimal_alt alt;
  _null_decimal_alt(&alt);
  alt.sign = _get_sign_std(std);
  alt.exp = _get_exp_std(std);
  int i = 0;
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 32; k++) alt.bits[i++] = _get_bit_int(std.bits[j], k);
  }
  return alt;
}

s21_decimal _convert_alt_to_std(s21_decimal_alt alt) {
  s21_decimal std;
  _init_decimal(&std);
  int k = 95;
  for (int i = 2; i >= 0; i--)
    for (int j = 31; j >= 0; j--)
      std.bits[i] = (std.bits[i] << 1) + alt.bits[k--];
  std.bits[3] = alt.sign;
  std.bits[3] <<= 7;
  k = 128;
  for (int i = 7; i >= 0; i--) {
    std.bits[3] <<= 1;
    if (alt.exp >= k) {
      alt.exp -= k;
      std.bits[3]++;
    }
    k >>= 1;
  }
  std.bits[3] <<= 16;
  return std;
}
