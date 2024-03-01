#include "s21_decimal.h"

// Округляет указанное Decimal число до
// ближайшего целого числа.

int s21_get_num(s21_decimal value, int num_to_get) {
  s21_set_scale(&value.bits[3], num_to_get - 1);
  s21_truncate(value, &value);
  return value.bits[0] % 10;
}

int is_round_up(s21_decimal value) {
  int pow = s21_get_scaling_f(value.bits[3]);
  int save_value = 0;
  if (s21_get_num(value, pow) >= 5) {  // получаем определённую цифру из числа
    save_value += 1;
  }
  return save_value;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int to_return = convertation_error;
  if (result) {
    s21_init_decimal(result);
    s21_rewrite_decimal(value, result);
    // printf("after rewrite res: %d %d %d %d\n", result->bits[0],
    // result->bits[1], result->bits[2], result->bits[3]);
    to_return = convertation_ok;
    int save_value = 0;
    if (is_round_up(value)) {  // проверяет, нужно ли увеличить число
      save_value = 1;
    }
    s21_truncate(value, &value);
    s21_set_scale(&value.bits[3], 0);
    s21_decimal one = {{save_value, 0, 0, 0}};
    s21_add(value, one, result);
  }
  return to_return;
}

// int main() {
//   s21_decimal num = {{1, 0, 0, 0 * pow(2, 16)}};
//   printf("%d\n", s21_round(num, NULL));
//   printf("%d %d %d %d\n", num.bits[0], num.bits[1], num.bits[2],
//   num.bits[3]);
// }
