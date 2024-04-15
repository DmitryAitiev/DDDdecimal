  #include <stdio.h>
    #include "s21_decimal.h"

    int main(){
        float result = 0;
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80010000}};
  int check = -321317241;

 int code = s21_from_decimal_to_float(decimal, &result);
    return 0;
    }