#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 0;

  if (dst) {
    nullify(dst);
  } else {
    status = 1;
  }

  if (status || (0 < fabsf(src) && fabsf(src) < 1e-28) || isnan(src) ||
      isinf(src) || 79228162514264337593543950335.f < src) {
    status = 1;
  } else {
    char part[128] = {0};
    int scale = 0;
    int float_part = 0;

    int length = 0;

    sprintf(part, "%.7g", src);

    get_float(part, &scale, &length, &float_part);

    if (scale < 0 && 28 < abs(scale) + length) {
      memset(part, 0, 128);

      sprintf(part, "%.*g", 29 - abs(scale), src);

      get_float(part, &scale, &length, &float_part);
    }

    int number = abs(atoi(part));

    for (int i = 0; i < length; ++i) {
      number *= 10;
    }

    number += float_part;

    if (src < 0) {
      setSign(dst, 1);
    }

    if (scale < 0) {
      set_scale(dst, abs(scale) + length);
    } else if (!scale) {
      set_scale(dst, length);
    }

    for (int i = 0; number; ++i, number /= 2) {
      if (number % 2) {
        set_bit(dst, i, 1);
      }
    }

    if (0 < scale - length) {
      s21_decimal s21_mul_by_10 = {{10, 0, 0, 0}};
      for (int i = 0; !status && i < scale - length; ++i) {
        status = s21_mul(*dst, s21_mul_by_10, dst);
      }
    }
  }

  return status;
}

void get_float(char *part, int *scale, int *length, int *float_part) {
  char *dot = strchr(part, '.');

  char *exponenta = strchr(part, 'e');

  *scale = 0;
  *float_part = 0;

  *length = 0;

  if (exponenta) {
    *exponenta++ = '\0';
    *scale = atoi(exponenta);
  }

  if (dot) {
    *dot++ = '\0';
    *length = strlen(dot);
    *float_part = atoi(dot);
  }
}