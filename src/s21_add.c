#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error=0;
    int sign1=extractBitSign(value_1);
    int sign2=extractBitSign(value_2);  
    unsigned int sign=0;  
    nullify(result);
    s21_big_decimal big1, big2, resbig;
    nullifyb(&big1);nullifyb(&big2);nullifyb(&resbig);
    int scale=normalize(value_1, value_2, &big1, &big2);
    if(sign1==sign2){
        sign=(unsigned int)sign1;
    myaddb(big1, big2, &resbig);
    error=mybig_to_decimal(resbig, result, scale, sign);}
    if(sign1!=sign2){
        if(extractBitSign(value_1)==1){
            setSign(&value_1, 0);
            s21_sub(value_2, value_1, result);
        }   
        else if(extractBitSign(value_2)==1){
            setSign(&value_2, 0);
            s21_sub(value_1, value_2, result);
    }
}
return error;
}
