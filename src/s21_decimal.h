#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUS_SIGN 2147483648
#define UINT_MAX 4294967295
#define INT_MIN -2147483648
#define MAX_BLOCK_NUMBER 96
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f
#define MAX_BLOCK_BITS 32

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  bool bits[192];
  bool sign;
  int exp;
} s21_decimal_alt;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_result;

typedef struct {
  unsigned sign;
  int scale;
  unsigned int bits[8];
} s21_big_decimal;

typedef enum s21_decimal_sign {
  S21_POSITIVE = 0,
  S21_NEGATIVE = 1
} s21_decimal_sign;

typedef enum s21_conversion_result {
  S21_CONVERSION_OK = 0,
  S21_CONVERSION_ERROR = 1
} s21_conversion_result;

typedef enum s21_comparison_result {
  S21_COMPARISON_FALSE = 0,
  S21_COMPARISON_TRUE = 1,
} s21_comparison_result;

typedef union decimal_bit3 {
  int i;
  struct {
    uint32_t empty2 : 16;
    uint32_t power : 8;
    uint32_t empty1 : 7;
    uint32_t sign : 1;
  } parts;
} decimal_bit3;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);

int _sub_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _add_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _mul_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _div_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);

bool _get_bit_int(unsigned int num, int pos);
void _right_shift(s21_decimal_alt *alt);
void _left_shift(s21_decimal_alt *alt);
bool _get_sign_std(s21_decimal dec);
int _get_exp_std(s21_decimal dec);
void _null_decimal_alt(s21_decimal_alt *alt);
s21_decimal_alt _convert_std_to_alt(s21_decimal std);
s21_decimal _convert_alt_to_std(s21_decimal_alt alt);
void _rescale(s21_decimal *value_1, s21_decimal *value_2);
void _rescale_alt(s21_decimal_alt *alt_value_1, s21_decimal_alt *alt_value_2);
void _rescale_alt_to_smaller(s21_decimal_alt *alt_value_1,
                             s21_decimal_alt *alt_value_2);
void _init_decimal(s21_decimal *decimal);
int _div_by_ten(s21_decimal_alt *alt);
bool _compare_bits(s21_decimal_alt alt1, s21_decimal_alt alt2);
bool _is_null(s21_decimal_alt alt);
int _last_bit(s21_decimal_alt alt);
void _bank_rounding(s21_decimal_alt *alt, int mod);
void _align(s21_decimal_alt *alt1, s21_decimal_alt *alt2);
void _rescale_alt_to_zero(s21_decimal_alt *alt_value_1,
                          s21_decimal_alt *alt_value_2);
s21_decimal_alt _div_with_modulo(s21_decimal_alt alt_value_1,
                                 s21_decimal_alt alt_value_2,
                                 s21_decimal_alt *alt_result);

/* big decimal function */
int s21_decimal_is_zero(s21_decimal dec);

/* base functions */
unsigned int set_mask(int index);
unsigned int get_bit(s21_decimal val, int bit);
void set_bit(s21_decimal *dec, int bit, int value);
int get_sign(s21_decimal dec);
int get_scale(s21_decimal dec);
void set_sign(s21_decimal *dec, int n);
void set_scale(s21_decimal *dec, int value);
int get_before_scale(s21_decimal dec);
int int_add_decimal(s21_decimal dec, int a, s21_decimal *res);
void normalization(s21_decimal *dec_one, s21_decimal *dec_two);
void equalization(int ext_big, int ext_small, s21_decimal *big_ext,
                  s21_decimal *small_ext);
int multiplay_by_ten(s21_decimal dec, s21_decimal *res);
int division_by_ten(s21_decimal dec, s21_decimal *res);

/* another functions */
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

void s21_clear_decimal(s21_decimal *decimal);
s21_decimal s21_decimal_get_int_min(void);
s21_decimal s21_decimal_get_zero(void);
s21_decimal s21_decimal_get_int_max(void);
s21_decimal s21_decimal_get_inf(void);
s21_decimal s21_float_string_to_decimal(char *str);
s21_decimal s21_decimal_get_from_char(char c);
s21_decimal s21_int128_get_ten_pow(int pow);
s21_decimal s21_decimal_get_one(void);
int s21_get_float_exp_from_string(char *str);

int s21_is_correct_decimal(s21_decimal decimal);
int s21_decimal_get_sign(s21_decimal decimal);
int s21_decimal_get_power(s21_decimal decimal);
int s21_decimal_get_empty1(s21_decimal decimal);
int s21_decimal_get_empty2(s21_decimal decimal);
int s21_decimal_is_set_bit(s21_decimal decimal, int index);
int s21_is_set_bit(int number, int index);
void s21_decimal_set_sign(s21_decimal *decimal, int sign);

#endif  // SRC_S21_DECIMAL_H_
