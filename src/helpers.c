#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_get_bit(int num, int ind) { return (num & (1 << ind)) ? 1 : 0; }

int s21_get_sign(int num) { return s21_get_bit(num, 31) ? 1 : 0; }

int s21_get_scaling_f(int value) {
  int result = value & SCALE_MASK;  // маска для коэффа масштабирования
  result = result >> 16;  // убрали 16 нулей лишних
  return result;
}

int s21_set_bit_1(int num, int ind) { return (num | (1 << ind)); }

int s21_set_bit_0(int num, int ind) { return (num & ~(1 << ind)); }

int s21_set_bit_mantissa(int index) {
  int num_to_return = -1;
  if (index < 31) num_to_return = 0;
  if (index <= 62 && index >= 31) num_to_return = 1;
  if (index <= 92 && index > 62) num_to_return = 2;
  if (index < 95 && index > 92) num_to_return = 3;
  return num_to_return;
}

void s21_divide_10(s21_decimal *value) {
  long long unsigned int mod = 0;
  long long int temp;
  for (int i = 2; i >= 0; i--) {
    temp = (mod << 32) + value->bits[i];  //
    mod = temp % 10;
    value->bits[i] = temp / 10;
  }
}

int s21_10_division(s21_decimal *dst) {
  int mod = 0;
  long long int tmp;
  for (int i = 2; i >= 0; i--) {
    tmp = dst->bits[i] + ((long long)(mod) << 32);
    mod = tmp % 10;
    dst->bits[i] = tmp / 10;
  }
  return mod;
}

int s21_divide_10_float(s21_decimal *dst) {
  s21_decimal tmp = {0};
  for (int i = 0; i < 3; i++) tmp.bits[i] = dst->bits[i];
  return !s21_10_division(&tmp);
}

void s21_set_scale(unsigned int *scale, int scale_to_set) {
  int sign = s21_get_sign(*scale);
  *scale = scale_to_set;
  *scale <<= 16;
  if (sign)
    *scale = s21_set_bit_1(*scale, 31);
  else
    *scale = s21_set_bit_0(*scale, 31);
}

void s21_rewrite_decimal(s21_decimal value, s21_decimal *result) {
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
  result->bits[3] = value.bits[3];
}

void s21_init_decimal(s21_decimal *dec) {
  for (int i = 0; i < BITS_NUMBER; i++) dec->bits[i] = 0;
}

int s21_count_exp(float src) {
  union data data;
  data.f = src;
  int expon = ((data.x & EXP) >> 23);
  return expon;
}

int s21_get_sign_from_float(float src) {
  union data data;
  data.f = src;
  return s21_get_bit(data.x, 31);
}

// Узнать, какой сейчас стоит знак (1: минус / 0: плюс)
int s21_getSign(s21_decimal num) {
  int sign;
  if ((num.bits[3] & (1 << 31)) == 0) {
    sign = 0;
  } else {
    sign = 1;
  }
  return sign;
}

// Узнать значение конкретного бита
int s21_getBit(s21_decimal num, int curBit) {
  int bit;
  if ((num.bits[curBit / 32] & (1 << curBit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }
  return bit;
}

int s21_getPower(s21_decimal num) {
  int power = 0;
  int counter = 0;
  int length = 16;
  while (length <= 23) {
    int bit = ((num.bits[3] & (1 << length)) != 0);
    power += bit * pow(2, counter);
    length++;
    counter++;
  }
  return power;
}

// проверка 0-95 нули
int s21_is_zeroed(s21_decimal value) {
  int result = TRUE;
  for (int i = 0; i < 96; i++) {
    if (s21_getBit(value, i) != 0) {
      result = FALSE;
    }
  }
  return result;
}

// меняем результат
int s21_switch_result(int result) {
  if (result == FALSE) {
    result = TRUE;
  } else if (result == TRUE) {
    result = FALSE;
  }
  return result;
}

int s21_add_over(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  short error = 0, tmp = 0;
  int bit_temp = 0;
  int bit_value = 0;
  s21_init_decimal(result);
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 32; i++) {
      bit_temp = s21_get_bit(value_1.bits[j], i);
      bit_value = s21_get_bit(value_2.bits[j], i);
      if (bit_temp && bit_value) {
        if (tmp) {
          result->bits[j] = s21_set_bit_1(result->bits[j], i);
        } else {
          tmp = 1;
        }
      } else if (bit_temp ^ bit_value) {
        if (!tmp) {
          result->bits[j] = s21_set_bit_1(result->bits[j], i);
        }
      } else if (tmp) {
        result->bits[j] = s21_set_bit_1(result->bits[j], i);
        tmp = 0;
      }
    }
    if (tmp && j == 3) error = 1;
  }
  return error;
}

s21_decimal s21_go_left(s21_decimal number, int shift) {
  for (int i = 0; i < shift; i++) {
    int tmp[5];
    for (int i = 0; i < 3; i++) {
      tmp[i] = s21_get_bit(number.bits[i], 31);
    }
    for (int i = 0; i < 4; i++) {
      number.bits[i] = number.bits[i] << 1;
    }
    for (int i = 0; i < 3; i++) {
      if (tmp[i]) {
        number.bits[i + 1] = s21_set_bit_1(number.bits[i + 1], 0);
      }
    }
  }
  return number;
}

s21_decimal s21_mul_ten(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  for (int i = 0; i < 128; i++) {
    if (s21_get_bit(value_1.bits[i / 32], i % 32)) {
      s21_init_decimal(&temp);
      s21_rewrite_decimal(result, &temp);
      s21_add_over(temp, s21_go_left(value_2, i), &result);
    }
  }
  return result;
}

int s21_overflow(s21_decimal *result, int scale) {
  int to_return = convertation_error;
  s21_decimal ten = {{10, 0, 0, 0}};
  for (int i = 0; i < scale; i++) {
    *result = s21_mul_ten(*result, ten);
  }
  if (result) {
    to_return = convertation_ok;
  }
  return to_return;
}