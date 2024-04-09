#include "s21_decimal.h"

//bool _get_bit_int(unsigned int num, int pos) { return (num >> pos) & 1; }

int _get_bit_int(unsigned int value, int bit_number) {
  return value & (1 << bit_number);
}

// сдвиг вправо для альтернативного децимала

s21_big_decimal mantissadecimalToBig(s21_decimal value) {
  s21_big_decimal result;
  initializeByBigZeros(&result);
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value.bits[i];
  }
  return result;
}

void set_bit_int(unsigned int *value, int bit_number, int set_value) {
  if (set_value) {
    *value |= (1 << bit_number);
  } else {
    *value = *value & ~(1 << bit_number);
  }
}

void add_one(s21_decimal *value) { 
  s21_decimal one = {{1}};

  s21_sum(value, one);
}

void initializeByBigZeros(s21_big_decimal *value) {
  (*value).bits[0] = 0;
  (*value).bits[1] = 0;
  (*value).bits[2] = 0;
  (*value).bits[3] = 0;
  (*value).bits[4] = 0;
  (*value).bits[5] = 0;
}

bool get_bit_value(s21_decimal target, int bit_number) {
  int index = 0;
  while (bit_number >= 32) {
    index++;
    bit_number -= 32;
  }

  bool x = 1 << bit_number & target.bits[index];
  return x;
}

/**
 * сдвиг влево для альтернативного децимала
 * нужно при умножении
 */

int myshiftleft(s21_big_decimal* d, int value) {
  int error = 0;
  if (value != 0) {
    unsigned int overflow = 0;
    unsigned int memory = 0;
    for (int i = 0; i <= 5; i++) {
      memory = d->bits[i];
      d->bits[i] <<= value;
      d->bits[i] |= overflow;
      overflow = memory >> (32 - value);
    }
    if (overflow > 0) error = 1;
  }
  return error;
}

int myshiftlefts(s21_decimal* d, int value) {
  int error = 0;
  unsigned int overflow = 0;
  unsigned int memory = 0;
  if (value > 0) {
    for (int i = 0; i < 3; i++) {
      memory = (unsigned int)d->bits[i];
      d->bits[i] <<= value;
      d->bits[i] |= overflow;
      overflow = memory >> (32 - value);
    }
  }
  if (overflow > 0) error = 1;
  return error;
}

void myshiftright(s21_big_decimal* d, int value) {
  unsigned int overflow = 0;
  unsigned int memory = 0;
  for (int i = 5; i >= 0; i--) {
    memory = d->bits[i];
    d->bits[i] >>= value;
    d->bits[i] |= overflow;
    overflow = memory << (32 - value);
  }
}

void nullify(s21_decimal *d) {
  d->bits[0] = 0u;
  d->bits[1] = 0u;
  d->bits[2] = 0u;
  d->bits[3] = 0u;
}

void nullifyb(s21_big_decimal *d) {
  d->bits[0] = 0u;
  d->bits[1] = 0u;
  d->bits[2] = 0u;
  d->bits[3] = 0u;
  d->bits[4] = 0u;
  d->bits[5] = 0u;
}

bool _get_sign_std(s21_decimal dec) { return _get_bit_int(dec.bits[3], 31); }

int _get_exp_std(s21_decimal dec) { return (dec.bits[3] % 2147483648) >> 16; }

int extractBitSign(s21_decimal number) {
  int result = (number.bits[3] & (1u << 31)) != 0;
  return result;
}


void _init_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

/**
 * сравнение битов первого и второго альтернативного децимала
 * не учитывает экспоненту
 * возвращает 1, если первое число больше или равно второму
 * 0 если второе число больше первого
 */

/**
 * "выравнивание" чисел
 * нужно в делении
 * превращает, например, 1001 и 10 в 1001 и 1000
 * но 1001 и 11 в 1001 и 110
 * по совершенно непонятным мне причинам не работает с div_by_ten
 */


// Степени числа 10
static const s21_decimal all_ten_pows[39] = {
    [0] = {{0x1, 0x0, 0x0, 0x0}},
    [1] = {{0xA, 0x0, 0x0, 0x0}},
    [2] = {{0x64, 0x0, 0x0, 0x0}},
    [3] = {{0x3E8, 0x0, 0x0, 0x0}},
    [4] = {{0x2710, 0x0, 0x0, 0x0}},
    [5] = {{0x186A0, 0x0, 0x0, 0x0}},
    [6] = {{0xF4240, 0x0, 0x0, 0x0}},
    [7] = {{0x989680, 0x0, 0x0, 0x0}},
    [8] = {{0x5F5E100, 0x0, 0x0, 0x0}},
    [9] = {{0x3B9ACA00, 0x0, 0x0, 0x0}},
    [10] = {{0x540BE400, 0x2, 0x0, 0x0}},
    [11] = {{0x4876E800, 0x17, 0x0, 0x0}},
    [12] = {{0xD4A51000, 0xE8, 0x0, 0x0}},
    [13] = {{0x4E72A000, 0x918, 0x0, 0x0}},
    [14] = {{0x107A4000, 0x5AF3, 0x0, 0x0}},
    [15] = {{0xA4C68000, 0x38D7E, 0x0, 0x0}},
    [16] = {{0x6FC10000, 0x2386F2, 0x0, 0x0}},
    [17] = {{0x5D8A0000, 0x1634578, 0x0, 0x0}},
    [18] = {{0xA7640000, 0xDE0B6B3, 0x0, 0x0}},
    [19] = {{0x89E80000, 0x8AC72304, 0x0, 0x0}},
    [20] = {{0x63100000, 0x6BC75E2D, 0x5, 0x0}},
    [21] = {{0xDEA00000, 0x35C9ADC5, 0x36, 0x0}},
    [22] = {{0xB2400000, 0x19E0C9BA, 0x21E, 0x0}},
    [23] = {{0xF6800000, 0x2C7E14A, 0x152D, 0x0}},
    [24] = {{0xA1000000, 0x1BCECCED, 0xD3C2, 0x0}},
    [25] = {{0x4A000000, 0x16140148, 0x84595, 0x0}},
    [26] = {{0xE4000000, 0xDCC80CD2, 0x52B7D2, 0x0}},
    [27] = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}},
    [28] = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}},
    [29] = {{0xA0000000, 0x6D7217CA, 0x431E0FAE, 0x1}},
    [30] = {{0x40000000, 0x4674EDEA, 0x9F2C9CD0, 0xC}},
    [31] = {{0x80000000, 0xC0914B26, 0x37BE2022, 0x7E}},
    [32] = {{0x0, 0x85ACEF81, 0x2D6D415B, 0x4EE}},
    [33] = {{0x0, 0x38C15B0A, 0xC6448D93, 0x314D}},
    [34] = {{0x0, 0x378D8E64, 0xBEAD87C0, 0x1ED09}},
    [35] = {{0x0, 0x2B878FE8, 0x72C74D82, 0x134261}},
    [36] = {{0x0, 0xB34B9F10, 0x7BC90715, 0xC097CE}},
    [37] = {{0x0, 0xF436A0, 0xD5DA46D9, 0x785EE10}},
    [38] = {{0x0, 0x98A2240, 0x5A86C47A, 0x4B3B4CA8}}};

s21_decimal s21_decimal_get_zero(void) {
  s21_decimal result;
  s21_clear_decimal(&result);

  return result;
}

void s21_clear_decimal(s21_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

s21_decimal s21_decimal_get_int_min(void) {
  s21_decimal result = {{0x80000000, 0x0, 0x0, 0x80000000}};

  return result;
}

s21_decimal s21_decimal_get_inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};

  return result;
}

//s21_decimal s21_float_string_to_decimal(char *str) {
//  int digits_counter = 6;
//  s21_decimal result = s21_decimal_get_zero();
//  char *ptr = str;
//
//  int exp = s21_get_float_exp_from_string(str);
//
//  while (*ptr) {
//    if (*ptr == '.') {
//      ++ptr;
//      continue;
//    } else if (*ptr >= '0' && *ptr <= '9') {
//      s21_decimal tmp = s21_decimal_get_zero();
//      s21_mul(s21_decimal_get_from_char(*ptr),
//              s21_int128_get_ten_pow(digits_counter), &tmp);
//      s21_add(result, tmp, &result);
//      --digits_counter;
//      ++ptr;
//    } else {
//      break;
//    }
//  }
//  exp = exp - 6;
//
//  if (exp > 0) {
//    s21_mul(result, s21_int128_get_ten_pow(exp), &result);
//  } else if (exp < 0) {
//    if (exp < -28) {
//      s21_div(result, s21_int128_get_ten_pow(28), &result);
//      exp += 28;
//    }
//    s21_div(result, s21_int128_get_ten_pow(-exp), &result);
//  }
//
//  return result;
//}

s21_decimal s21_decimal_get_from_char(char c) {
  s21_decimal result;

  switch (c) {
    case '0':
      result = s21_decimal_get_zero();
      break;
    case '1':
      result = s21_decimal_get_one();
      break;
    case '2':
      s21_from_int_to_decimal(2, &result);
      break;
    case '3':
      s21_from_int_to_decimal(3, &result);
      break;
    case '4':
      s21_from_int_to_decimal(4, &result);
      break;
    case '5':
      s21_from_int_to_decimal(5, &result);
      break;
    case '6':
      s21_from_int_to_decimal(6, &result);
      break;
    case '7':
      s21_from_int_to_decimal(7, &result);
      break;
    case '8':
      s21_from_int_to_decimal(8, &result);
      break;
    case '9':
      s21_from_int_to_decimal(9, &result);
      break;
  }

  return result;
}

s21_decimal s21_int128_get_ten_pow(int pow) { return all_ten_pows[pow]; }

s21_decimal s21_decimal_get_one(void) {
  s21_decimal result;
  s21_clear_decimal(&result);
  result.bits[0] = 1;

  return result;
}

int s21_is_correct_decimal(s21_decimal decimal) {
  int code = 1;

  if (s21_decimal_get_empty1(decimal) != 0 ||
      s21_decimal_get_empty2(decimal) != 0) {
    code = 0;
  } else {
    int power = s21_decimal_get_power(decimal);
    if (power < 0 || power > 28) {
      code = 0;
    }
  }

  return code;
}

int s21_decimal_get_sign(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.sign;
}

int s21_decimal_get_power(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.power;
}

int s21_decimal_get_empty1(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.empty1;
}

int s21_decimal_get_empty2(s21_decimal decimal) {
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.empty2;
}

int s21_decimal_is_set_bit(s21_decimal decimal, int index) {
  return s21_is_set_bit(decimal.bits[index / MAX_BLOCK_BITS],
                        index % MAX_BLOCK_BITS);
}

int s21_is_set_bit(int number, int index) { return !!(number & (1U << index)); }

s21_decimal s21_decimal_get_int_max(void) {
  // MAX_INT = 2147483647
  s21_decimal result = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

  return result;
}

int s21_get_float_exp_from_string(char *str) {
  int result = 0;
  char *ptr = str;
  while (*ptr) {
    if (*ptr == 'E') {
      ++ptr;
      result = strtol(ptr, NULL, 10);
      break;
    }
    ++ptr;
  }

  return result;
}

int mybig_to_decimal(s21_big_decimal big, s21_decimal *decimal, int scale, unsigned int sign){
    nullify(decimal);
    int error=0;
    if((check_345_b(big)>0&&scale>0)||scale>28){
        int mod=div_by_tenb(&big);
        scale--;
        _bank_rounding(&big, decimal, mod, &scale, sign);
    }
    int wtf=check_345_b(big);
    if(wtf>0){
       error=(sign==1)?2:1;
        return error;}
for(int i=0;i<3;i++){
    decimal->bits[i]=big.bits[i];
}
decimal->bits[3]|=scale<<16;
setSign(decimal, sign);
return error;
}

int check_345_b(s21_big_decimal big) {
  int result = 0;
  if (big.bits[3] > 0 || big.bits[4] > 0 || big.bits[5] > 0) {
    result = 1;
  }
  return result;
}

int tsuboika_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  s21_big_decimal big1, big2;
  nullifyb(&big1);nullifyb(&big2);
  if (!s21_decimal_is_zero(dec1) && !s21_decimal_is_zero(dec2)) {
    if (retrieveBit(dec1, 127) < retrieveBit(dec2, 127)) {
      res = 1;
    } else if (retrieveBit(dec1, 127) > retrieveBit(dec2, 127)) {
      res = 0;
    } else {
      normalize(dec1, dec2, &big1, &big2);
      for (int i = 191; i >= 0; --i) {
        if (getBigBit(big1, i) > getBigBit(big2, i)) {
          
            res = 1;
          
          break;
        } else if (getBigBit(big1, i) < getBigBit(big2, i)) {
          
            res = 0;
          
          break;
        }
      }
    }
  }
  if(!s21_decimal_is_zero(dec1)&&s21_decimal_is_zero(dec2)){
res =1;
  }
  return res;
}

int tsuboika_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int res = 0;
  s21_big_decimal big1, big2;
  nullifyb(&big1);nullifyb(&big2);
  normalize(dec1, dec2, &big1, &big2);
  if (big1.bits[0] == big2.bits[0] && big1.bits[1] == big2.bits[1] && big1.bits[2] == big2.bits[2] && big1.bits[3] == big2.bits[3] && big1.bits[4] == big2.bits[4]&& big1.bits[5] == big2.bits[5]) {
    res = 1;
  }
  return res;
}

int retrieveBit(s21_decimal number, int bit) {
  return (number.bits[bit / 32] & (1u << (bit % 32))) != 0;
}

int getBigBit(s21_big_decimal value, int index) {
  int bits_index = index / 32;
  int int_index = 31 - index % 32;
  int bit = -1;
  if (index > -1 && index < 192) {
    value.bits[bits_index] = value.bits[bits_index] << int_index;
    value.bits[bits_index] = value.bits[bits_index] >> 31;
    bit = value.bits[bits_index] == 0 ? 0 : 1;
  }
  return bit;
}