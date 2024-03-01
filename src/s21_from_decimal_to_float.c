#include "s21_decimal.h"

// #define EXP (0xff << 23)
// #define BITS_NUMBER 4
// #define NUM_AFTER_POINT 1000000
// #define MINUS 2147483648
// #define MIN_DECIMAL 1e-28
// #define MAX_DECIMAL 79228162514264337593543950335
// #define INF 1.0 / 0.0
// #define SCALE_MASK 8355840

// enum state { FALSE = 0, TRUE = 1 };

// typedef struct {
//   unsigned int bits[4];
// } s21_decimal;

// typedef enum {
//   convertation_ok = 0,
//   convertation_error = 1,
// } convertation_errors;

// union data {
//   float f;
//   int x;
// };

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int to_return = convertation_ok;
  if (dst) {
    *dst = 0;
    int scaling_factor =
        s21_get_scaling_f(src.bits[3]);  // коэфф масштабирования
    int sign = s21_get_sign(src.bits[3]);  // знак
    for (int i = 0; i < 95; i++) {
      int mantissa = s21_set_bit_mantissa(i);  // в какой бит идем
      if (s21_get_bit(src.bits[mantissa], i % 31))
        *dst += pow(2, i);  // переводим во флот
    }
    while (scaling_factor > 0) {
      *dst /= 10;
      scaling_factor--;
    }
    if (sign) *dst *= -1;
  } else {
    to_return = convertation_error;
  }
  return to_return;
}

// int main(void) {
//   s21_decimal src = {{9768050, 0, 0, 5 * pow(2, 16)}};
//   float dst = 0;
//   s21_from_decimal_to_float(src, &dst);
//   printf("dst: %f\n", dst);
//   return 0;
// }