#include "s21_decimal.h"

int s21_is_greater(s21_decimal mem1, s21_decimal mem2){   //ИСПРАВИТЬ В ЧЕТВЕРГ
int res=0;
s21_big_decimal big1, big2;
nullifyb(&big1);
nullifyb(&big2);
normalize(mem1, mem2, &big1, &big2);
for (int i=192; i>0;i--){
    if (get_bit_value(mem1, i)!=get_bit_value(mem2, i))
    { 
     if (get_bit_value(mem1, i))
        res=1;
     break;
    }
}
    return res;
}

int s21_is_less(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2) ? 0 : 1);
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_less(dec1, dec2) ? 1 : 0);
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2) {
  return (s21_is_equal(dec1, dec2) || s21_is_greater(dec1, dec2) ? 1 : 0);
}

int s21_is_equal(s21_decimal mem1, s21_decimal mem2){
int res=1;
s21_big_decimal big1, big2;
nullifyb(&big1);
nullifyb(&big2);
normalize(mem1, mem2, &big1, &big2);
for (int i=192; i>0;i--){
    if (get_bit_value(mem1, i)!=get_bit_value(mem2, i))
    res*=0;
}
    return res;
}

int s21_is_not_equal(s21_decimal mem1, s21_decimal mem2){
int res=1;
s21_big_decimal big1, big2;
nullifyb(&big1);
nullifyb(&big2);
normalize(mem1, mem2, &big1, &big2);
for (int i=192; i>0;i--){
    if (get_bit_value(mem1, i)==get_bit_value(mem2, i))
    res*=0;
}
    return res;
}
