#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int to_return = convertation_error;
  if (dst && src != INF) {
    double temp = (double)src;
    to_return = convertation_ok;
    int sign = s21_get_sign_from_float(src);
    s21_init_decimal(dst);
    int count_exp = s21_count_exp(src);
    if (count_exp < 256) {
      if (src != 0) {
        int scale = 0;
        temp = fabs(temp);
        while (!floor(temp)) {  // если что-то меньше 1
          temp *= 10;
          scale++;
        }
        if (scale < 29) {
          while (!floor(temp / NUM_AFTER_POINT) && scale < 28) {
            temp *= 10;
            scale += 1;
          }
          double ost = 0;
          if (modf(temp, &ost) > 0.5) {
            temp++;
          }
          dst->bits[0] = temp;
          while (s21_divide_10_float(dst) && scale > 0) {
            s21_10_division(dst);
            scale--;
          }
          dst->bits[3] = scale << 16;
          if (sign)
            dst->bits[3] = s21_set_bit_1(dst->bits[3], 31);
          else
            dst->bits[3] = s21_set_bit_0(dst->bits[3], 31);
        } else
          to_return = convertation_error;
      }
    } else
      to_return = convertation_error;
  }
  return to_return;
}
