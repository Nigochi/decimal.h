#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int to_return = convertation_ok;
  int sign = -2;
  if (dst) {
    sign = s21_get_sign(src.bits[3]);
    s21_truncate(src, &src);
    if (sign == 1) {
      sign = -1;
    }
    if (sign == 0) {
      sign = 1;
    }
    *dst = src.bits[0] * sign;
  } else {
    to_return = convertation_error;
  }
  return to_return;
}