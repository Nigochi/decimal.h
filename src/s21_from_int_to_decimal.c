#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int to_return = convertation_ok;
  if (src) {
    s21_init_decimal(dst);
    if (src < 0) {
      dst->bits[3] = MINUS;
      src *= -1;
    }
    dst->bits[0] = src;
  } else {
    to_return = convertation_error;
  }
  return to_return;
}