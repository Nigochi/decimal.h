#include "s21_decimal.h"

// Округляет указанное Decimal число до
// ближайшего целого числа в сторону отрицательной бесконечности.

int s21_floor(s21_decimal value, s21_decimal *result) {
  int to_return = convertation_error;
  if (result) {
    to_return = convertation_ok;
    s21_init_decimal(result);
    s21_decimal one = {{1, 0, 0, 0}};
    to_return = s21_truncate(value, result);
    int sign = s21_get_sign(result->bits[3]);
    if (sign && s21_is_not_equal(value, *result)) {
      s21_sub(*result, one, result);
    }
    result->bits[3] = 0;
    if (sign)
      result->bits[3] = s21_set_bit_1(result->bits[3], 31);
    else
      result->bits[3] = s21_set_bit_0(result->bits[3], 31);
  }
  return to_return;
}
