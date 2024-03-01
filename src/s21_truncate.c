#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = convertation_error;
  if (result) {
    /* надо инициализировать переменную с результатом
    и потом положить в нее децимал с учетом
    коэффициента масштабирования,
    т.е. берем число и делим на 10 до победного*/
    s21_init_decimal(result);
    int scaling_factor =
        s21_get_scaling_f(value.bits[3]);  // достали коэфф масштабирования
    int sign = s21_get_sign(value.bits[3]);  // достали знак
    for (int i = scaling_factor; i > 0; i--) {
      s21_divide_10(&value);  // делит на 10 весь децимал
    }
    /* сейчас в value лежит нужный decimal
       который будет перезаписан в result */
    s21_rewrite_decimal(value, result);
    result->bits[3] = 0;
    if (sign)
      result->bits[3] = s21_set_bit_1(result->bits[3], 31);
    else
      result->bits[3] = s21_set_bit_0(result->bits[3], 31);
    error = convertation_ok;
  }
  return error;
}
