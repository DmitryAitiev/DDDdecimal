#include "s21_decimal.h"

// index = 94
// получается что в bits[2] в 30 индексе будет 1, а везде 0
unsigned int set_mask(int index) { return 1u << (index % 32); }

// bit - от 0 до 95
unsigned int get_bit(s21_decimal val, int bit) {
  unsigned int mask = set_mask(bit);
  return (val.bits[bit / 32] & mask) != 0;  // МОЖЕМ УБРАТЬ УСЛОВИЕ???????
}

void set_bit(s21_decimal *dec, int bit, int value) {
  if (value == 1) {
    dec->bits[bit / 32] |= (set_mask(bit));
  } else if (value == 0) {
    dec->bits[bit / 32] &= ~(set_mask(bit));
  }
}

int get_sign(s21_decimal dec) { return get_bit(dec, 127); }  // получаем знак

int get_scale(s21_decimal dec) {
  return (dec.bits[3] & (255 << 16)) >> 16;
}  // получаем степень
// 255 << 16 побитовая маска где все 1 в битах 16-23
// >>16 возвращаем на место чтобы получить норм число

void setSign(s21_decimal *value, unsigned int sign) {
  set_bit(value, 127, sign);
}  // устанавливаем знак + или -

void set_scale(s21_decimal *dec, int value) {  // устанавливаем степень
  dec->bits[3] = get_bit(*dec, 127) << 31 | value << 16;
}

int get_before_scale(s21_decimal dec) { return (dec.bits[3] & 32767); }

int int_add_decimal(s21_decimal dec, int a, s21_decimal *res) {
  int error = 0;
  s21_decimal value = {0};
  int sign = (a < 0) ? 1 : 0;
  if (sign) s21_negate(value, &value);
  value.bits[0] = abs(a);
  error = s21_add(dec, value, res);
  return error;
}

int normalize(s21_decimal num_1, s21_decimal num_2, s21_big_decimal *big1,  s21_big_decimal *big2) {
  *big1 = mantissadecimalToBig(num_1);
  *big2 = mantissadecimalToBig(num_2);
  int scale_1 = get_scale(num_1);
  int scale_2 = get_scale(num_2);
  int scale = 0;
  if (scale_1 == scale_2) {
    return scale_1;
  }
  if (scale_1 > scale_2) {
    for (int i = 0; i < abs(scale_1 - scale_2); i++) {
      mymulby10(big2);
    }
    scale = scale_1;
  } else {
    for (int i = 0; i < abs(scale_1 - scale_2); i++) {
      mymulby10(big1);
    }
    scale = scale_2;
  }
  return scale;
}

void mysubb(s21_big_decimal value_1, s21_big_decimal value_2,
           s21_big_decimal* result) {
  nullifyb(result);
  int res = 0;
  int k = 1;
  for (int i = 0; i < 191; i++) {
    res = get_bit_valueb(value_1, i) - get_bit_valueb(value_2, i);
    if (res == -1) {
      res = 1;
      for (k = 1; k + i < 191 && !get_bit_valueb(value_1, i + k); k++) {
      }

      s21_set_bitb(&value_1, k + i, 0);
      k--;
      if (k + i < 191) {
        while (k + i > i) {
          s21_set_bitb(&value_1, k + i, 1);
          k--;
        }
      }
    }
    s21_set_bitb(result, i, res);
  }
}

void s21_set_bitb(s21_big_decimal* num, int index, int value) {
    if (value == 1) {
    num->bits[index / 32] = num->bits[index / 32] | (1u << index % 32); // (1 << bit % 32) создает число, у которого только один бит равен 1 на позиции bit % 32
  } else if (value == 0) {
    num->bits[index / 32] = num->bits[index / 32] & ~(1u << index % 32); // инвертированная маска
  }
}


// умножение мантиссы на 10
int mymulby10(s21_big_decimal* d) {
  int error=0;
    s21_big_decimal shift3=*d;
 s21_big_decimal shift1=*d;

 error=myshiftleft(&shift3, 3);
 myshiftleft(&shift1, 1);

 myaddb(shift3, shift1, d);
 return error;
}

int s21_sum(s21_decimal *dst, s21_decimal src) {
  s21_decimal result = {0};
  int s = 0, c = 0, count = 0;
  int check_max = 0;
  for (int j = 0; j < 3; j++) {
    result.bits[j] = 0;
    for (int i = 0; i < 32; i++) {
      int v1 = (src.bits[j] >> i) & 1;
      int v2 = (dst->bits[j] >> i) & 1;
      // c = count ? 1 : c;
      if (c) {
        s = (v1 ^ v2) ^ c;
        c = (v1 & v2 & 1) | ((v1 ^ v2) & c);
      } else {
        s = (v1 ^ v2);
        c = v1 & v2 & 1;
      }
      result.bits[j] |= s << i;
      if ((i == 31) && c) {
        count = 1;
      }
      count = c;
    }
    dst->bits[j] = result.bits[j];
  }
  check_max = count;
  return check_max;
}

// деление мантиссы на 10
int division_by_ten(s21_decimal dec, s21_decimal *res) {
  uint64_t tmp_u;
  uint64_t remained = 0;
  for (int i = 2; i > -1; i--) {
    tmp_u = dec.bits[i];
    tmp_u |= remained << 32;
    remained = tmp_u % 10;
    tmp_u /= 10;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return remained;
}

int myaddb(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result){

    int error=0;
    nullifyb(result);
    int res=0;
    int carry=0;
    for(int i=0;i<191;i++){
       res=get_bit_valueb(value_1, i)+get_bit_valueb(value_2, i)+carry;
       s21_set_bitb(result, i, res%2);
       carry=res/2;
    }
    if(carry){error=1;}
    return error;
}

void mine_from_int_to_decimal(int src, s21_decimal *dst) {
  if (src < 0) {
    dst->bits[3] = 0b10000000000000000000000000000000;
  } else {
    dst->bits[3] = 0b00000000000000000000000000000000;
  }
  src = abs(src);
  dst->bits[0] = src;
  dst->bits[1] = 0b00000000000000000000000000000000;
  dst->bits[2] = 0b00000000000000000000000000000000;
}

void mine_from_int_to_decimalb(int src, s21_big_decimal *dst) {
  src = abs(src);
  dst->bits[0] = src;
  dst->bits[1] = 0b00000000000000000000000000000000;
  dst->bits[2] = 0b00000000000000000000000000000000;
  dst->bits[3] = 0b00000000000000000000000000000000;
  dst->bits[4] = 0b00000000000000000000000000000000;
  dst->bits[5] = 0b00000000000000000000000000000000;
}

bool get_bit_valueb(s21_big_decimal target, int bit_number) {
  int index = 0;
  while (bit_number >= 32) {
    index++;
    bit_number -= 32;
  }

  bool x = 1u << bit_number & target.bits[index];
  return x;
}

int countLastBitbig(s21_big_decimal d) {
  int counter = 127;
  while ((counter >= 0) && (!get_bit_valueb(d, counter))) {
    counter--;
  }
  return counter;
}

int div_by_tenb(s21_big_decimal* result) {
  unsigned long long overflow = 0;
  for (int i = 5; i >= 0; i--) {
    unsigned long long save = (overflow << 32) | result->bits[i];
    result->bits[i] = (save / 10);
    overflow = save % 10;
  }
  return overflow;
}