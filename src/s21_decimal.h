#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINUS_SIGN 2147483648
#define UINT_MAX 4294967295
#define INT_MIN -2147483648
#define MAX_BLOCK_NUMBER 96
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f
#define MAX_BLOCK_BITS 32
#define MAX_UINT 4294967295 

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
int s21_sub(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result);
int s21_mul(s21_decimal val1, s21_decimal val2,
                        s21_decimal* result);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);

int _get_bit_int(unsigned int num, int pos);
int extractBitSign(s21_decimal number);
void nullify(s21_decimal *d);
void nullifyb(s21_big_decimal *d);
int myshiftleft(s21_big_decimal* d, int value);
int myshiftlefts(s21_decimal* d, int value);
void myshiftright(s21_big_decimal* d, int value);
bool _get_sign_std(s21_decimal dec);
int _get_exp_std(s21_decimal dec);
void _rescale(s21_decimal *value_1, s21_decimal *value_2);
void _init_decimal(s21_decimal *decimal);
void set_bit_int(unsigned int *value, int bit_number, int set_value);
void add_one(s21_decimal *value);
int div_by_tenb(s21_big_decimal *result);
void _bank_rounding(s21_big_decimal* big, s21_decimal* decimal, int mod, int* scale, unsigned int sign);
int rem_div_by_ten(s21_decimal value);

/* big decimal function */
int s21_decimal_is_zero(s21_decimal dec);

/* base functions */
unsigned int set_mask(int index);
unsigned int get_bit(s21_decimal val, int bit);
void set_bit(s21_decimal *dec, int bit, int value);
int get_sign(s21_decimal dec);
int get_scale(s21_decimal dec);
void setSign(s21_decimal *value, unsigned int sign);
int check_345_b(s21_big_decimal big);
void set_scale(s21_decimal *dec, int value);
bool get_bit_value(s21_decimal target, int bit_number);
int get_before_scale(s21_decimal dec);
int int_add_decimal(s21_decimal dec, int a, s21_decimal *res);
int normalize(s21_decimal num_1, s21_decimal num_2,
                         s21_big_decimal *big1,
                         s21_big_decimal *big2);
int mymulby10(s21_big_decimal* d);
int s21_sum(s21_decimal *dst, s21_decimal src);
int division_by_ten(s21_decimal dec, s21_decimal *res);
s21_big_decimal mantissadecimalToBig(s21_decimal value);
int myaddb(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);
int mybig_to_decimal(s21_big_decimal big, s21_decimal *decimal, int scale, unsigned int sign);
int tsuboika_is_greater(s21_decimal dec1, s21_decimal dec2);
int tsuboika_is_equal(s21_decimal dec1, s21_decimal dec2);
int retrieveBit(s21_decimal number, int bit);
int getBigBit(s21_big_decimal value, int index);
void mysubb(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal* result);
void mine_from_int_to_decimal(int src, s21_decimal *dst);
void mine_from_int_to_decimalb(int src, s21_big_decimal *dst);
bool get_bit_valueb(s21_big_decimal target, int bit_number);
int countLastBitbig(s21_big_decimal d);
void s21_set_bitb(s21_big_decimal* num, int index, int value);
void initializeByBigZeros(s21_big_decimal *value);
void get_float(char *part, int *scale, int *length, int *float_part);
int myaddnormalize(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result);
int mysubnormalize(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal* result);

/* another functions */
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif  // SRC_S21_DECIMAL_H_
