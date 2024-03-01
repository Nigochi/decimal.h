#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXP (0xff << 23)
#define BITS_NUMBER 4
#define NUM_AFTER_POINT 1000000
#define MINUS 2147483648
#define MIN_DECIMAL 1e-28
#define MAX_DECIMAL 79228162514264337593543950335
#define INF 1.0 / 0.0
#define SCALE_MASK 8355840

enum state { FALSE = 0, TRUE = 1 };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef enum {
  convertation_ok = 0,
  convertation_error = 1,
} convertation_errors;

union data {
  float f;
  int x;
};

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

int s21_get_bit(int num, int ind);
int s21_get_sign(int num);
int s21_get_scaling_f(int value);
int s21_set_bit_1(int num, int ind);
int s21_set_bit_0(int num, int ind);
void s21_divide_10(s21_decimal *value);
void s21_set_scale(unsigned int *scale, int scale_to_set);
void s21_rewrite_decimal(s21_decimal value, s21_decimal *result);
void s21_init_decimal(s21_decimal *dec);
int s21_set_bit_mantissa(int index);
int s21_10_division(s21_decimal *dst);
int s21_divide_10_float(s21_decimal *dst);
int s21_count_exp(float src);
int s21_get_sign_from_float(float src);

// bits & other
int s21_getBit(s21_decimal num, int curBit);
int s21_getSign(s21_decimal num);
int s21_getPower(s21_decimal num);
int s21_is_zeroed(s21_decimal value);
int s21_switch_result(int result);

// comparison
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_overflow(s21_decimal *result, int scale);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

#endif  // S21_DECIMAL_H_
