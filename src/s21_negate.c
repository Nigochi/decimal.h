#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int to_return = convertation_error;
  if (result) {
    to_return = convertation_ok;
    s21_init_decimal(result);
    s21_rewrite_decimal(value, result);
    if (result->bits[3] == MINUS)
      result->bits[3] = s21_set_bit_0(result->bits[3], 31);
    else {
      result->bits[3] = s21_set_bit_1(result->bits[3], 31);
    }
  }
  return to_return;
}
