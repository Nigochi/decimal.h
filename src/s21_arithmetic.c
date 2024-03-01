#include "s21_decimal.h"

long lfabs(long znach) {
  if (znach < 0) {
    znach *= -1;
  }
  return znach;
}

int num_of_degree(s21_decimal value) {
  return (value.bits[3] - MINUS * (value.bits[3] / MINUS)) / pow(2, 16);
}

void case_of_full(long long *save_value, s21_decimal *result) {
  if ((long)result->bits[1] + 1 >= 2 * MINUS) {
    if ((long)result->bits[2] + 1 >= 2 * MINUS) {
      (*save_value) += 1;
    }
    result->bits[2] += 1;
  }
  result->bits[1] += 1;
}

void opred_result_by_okr(long long *save_value, s21_decimal value_1,
                         s21_decimal value_2, s21_decimal *result) {
  while ((*save_value || num_of_degree(*result) > 28) &&
         num_of_degree(*result) > 0) {
    int mod_save_value = *save_value % 10;
    *save_value /= 10;
    for (int bits_part = 2; bits_part != -1; bits_part--) {
      long long sub = result->bits[bits_part] + (mod_save_value)*pow(2, 32);
      if (bits_part == 0 &&
          ((sub % 10 == 5 && ((sub / 10) % 10) % 2 == 1) || sub % 10 > 5)) {
        sub += 10;
      }
      mod_save_value = sub % 10;
      result->bits[bits_part] = sub / 10;
      if (sub / 10 >= 2 * MINUS) {
        case_of_full(save_value, result);
      }
    }
    result->bits[3] -= pow(2, 16);
  }
  if (value_1.bits[3] / MINUS == 1 && value_2.bits[3] / MINUS == 1) {
    if (*save_value >= 0) {
      result->bits[3] += MINUS;
    }
    if (*save_value >= 1) {
      *save_value = -1;
    }
  }
}

// int max_position(s21_decimal value_1, s21_decimal value_2,
//                  int pokazatel_stepeni) {
//   long value1 = value_1.bits[2] * pow(-1, value_1.bits[3] / MINUS) *
//                 pow(10, ((pokazatel_stepeni <= 0) ? -pokazatel_stepeni : 0));
//   long value2 = value_2.bits[2] * pow(-1, value_2.bits[3] / MINUS) *
//                 pow(10, ((pokazatel_stepeni >= 0) ? pokazatel_stepeni : 0));
//   long result =
//       (value1 == 0 && value2 == 0) ? 0 : (int)log2(lfabs(fmax(value1,
//       value2)));
//   return result;
// }

int error_flag(int save_value) {
  int error_znach = 0;
  if (save_value >= 1) {
    error_znach = 1;
  }
  if (save_value <= -1) {
    error_znach = 2;
  }
  return error_znach;
}

int num_of_znach(int max_position) {
  int result = (max_position - 31) / 8 +
               ((max_position - 31) - ((max_position - 31) / 8) * 8 > 0);
  return result;
}

long value_of_compare_bits(s21_decimal value, int bits_part,
                           int pokazatel_stepeni) {
  int sign = pow(-1, value.bits[3] / MINUS);
  int power = pow(10, ((pokazatel_stepeni >= 0) ? pokazatel_stepeni : 0));
  return ((long)value.bits[bits_part] * sign * power);
}

int is_inverse(s21_decimal value_1, s21_decimal value_2) {
  value_2.bits[3] += MINUS;
  int prob_1 = s21_is_less(value_1, value_2) && value_1.bits[3] / MINUS == 0 &&
               value_2.bits[3] / MINUS == 0;
  value_2.bits[3] -= MINUS;
  value_1.bits[3] += MINUS;
  int prob_2 = s21_is_less(value_2, value_1) && value_1.bits[3] / MINUS == 1 &&
               value_2.bits[3] / MINUS == 1;
  value_1.bits[3] -= MINUS;
  return (prob_1 || prob_2);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_init_decimal(result);
  if (is_inverse(value_1, value_2)) {
    value_1.bits[3] += MINUS;
    value_2.bits[3] += MINUS;
    result->bits[3] = MINUS;
  }
  int pokazatel_stepeni = num_of_degree(value_1) - num_of_degree(value_2);
  long long save_value = 0;
  for (int bits_part = 0; bits_part != 3; bits_part++) {
    long value1 = value_of_compare_bits(value_1, bits_part, -pokazatel_stepeni);
    long value2 = value_of_compare_bits(value_2, bits_part, pokazatel_stepeni);
    long long sum_value =
        (value1 + value2) *
            pow(-1, (value_2.bits[3] / MINUS + value_1.bits[3] / MINUS) / 2) +
        save_value;
    result->bits[bits_part] = (unsigned)(sum_value);
    save_value = 0;
    if (sum_value < 0) {
      save_value = -1;
    }
    if (sum_value >= 2 * MINUS) {
      save_value = sum_value / (2 * MINUS);
    }
  }
  result->bits[3] += (num_of_degree(value_1) > num_of_degree(value_2))
                         ? (num_of_degree(value_1) * 65536)
                         : (num_of_degree(value_2) * 65536);
  opred_result_by_okr(&save_value, value_1, value_2, result);
  return error_flag(save_value);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  value_2.bits[3] += MINUS;
  return s21_add(value_1, value_2, result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_init_decimal(result);
  long long save_value = 1;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = (value_1.bits[3] - MINUS * (value_1.bits[3] / MINUS) +
                     value_2.bits[3] - MINUS * (value_2.bits[3] / MINUS)) +
                    ((1 - 2 * (value_1.bits[3] / MINUS)) *
                                 (1 - 2 * (value_2.bits[3] / MINUS)) <
                             0
                         ? MINUS
                         : 0);
  // if(!((long long)(value_1.bits[0])*(long long)(value_2.bits[2]) >= 2*MINUS
  // (long long)(value_1.bits[1])*(long long)(value_2.bits[1]) >= 2*MINUS
  // (long long)(value_1.bits[2])*(long long)(value_2.bits[0]) >= 2*MINUS
  // (long long)(value_1.bits[2])*(long long)(value_2.bits[1]) > 0  (long
  // long)(value_1.bits[1])*(long long)(value_2.bits[2]) > 0 || (long
  // long)(value_1.bits[2])*(long long)(value_2.bits[2]) > 0)){
  save_value = 0;
  for (int bits_part_2 = 0; bits_part_2 != 3 && save_value == 0;
       bits_part_2++) {
    for (int bits_part_1 = 0;
         bits_part_1 != 3 && bits_part_1 + bits_part_2 <= 2; bits_part_1++) {
      result->bits[bits_part_1 + bits_part_2] +=
          (long long)(value_1.bits[bits_part_1]) *
              (long long)(value_2.bits[bits_part_2]) -
          ((long long)(value_1.bits[bits_part_1]) *
           (long long)(value_2.bits[bits_part_2]) / (2 * MINUS)) *
              (2 * MINUS) +
          save_value;
      save_value = (long long)(value_1.bits[bits_part_1]) *
                   (long long)(value_2.bits[bits_part_2]) / (2 * MINUS);
    }
  }
  opred_result_by_okr(&save_value, value_1, value_2, result);
  // }
  return error_flag(save_value ? 1 - 2 * (result->bits[3] / MINUS) : 0);
}

// int main() {
//   s21_decimal bits1 = {{20, 0, 0, 2 * pow(2, 16)}};
//   s21_decimal bits2 = {{20, 0, 0, 1 * pow(2, 16)}}, result;
// int error = s21_add(bits1, bits2, &result);
//   if (!error) {
//     if (bits1.bits[3] / MINUS == 1) {
//       printf("\n - ");
//     } else {
//       printf("\n + ");
//     }
//     for (int j = 2; j >= 0; j--) {
//       // printf("%u", (unsigned int)(bits1.bits[j]));
//       for (int i = 31; i >= 0; i--) {
//         printf("%d", (unsigned int)fmod(bits1.bits[j] / pow(2, i), 2));
//       }
//       printf(" ");
//     }
//     printf("%d\n",
//            (int)(bits1.bits[3] - MINUS * (bits1.bits[3] / MINUS)) / 65536);
//     if (bits2.bits[3] / MINUS == 1) {
//       printf(" - ");
//     } else {
//       printf(" + ");
//     }
//     for (int j = 2; j >= 0; j--) {
//       // printf("%u", (unsigned int)(bits2.bits[j]));
//       for (int i = 31; i >= 0; i--) {
//         printf("%d", (unsigned int)fmod(bits2.bits[j] / pow(2, i), 2));
//       }
//       printf(" ");
//     }
//     printf("%d\n",
//            (int)(bits2.bits[3] - MINUS * (bits2.bits[3] / MINUS)) / 65536);
//     if (result.bits[3] / MINUS == 1) {
//       printf(" - ");
//     } else {
//       printf(" + ");
//     }
//     for (int j = 2; j >= 0; j--) {
//       // printf("%u", (unsigned int)(result.bits[j]));
//       for (int i = 31; i >= 0; i--) {
//         printf("%d", (unsigned int)fmod(result.bits[j] / pow(2, i), 2));
//       }
//       printf(" ");
//     }
//     printf("%d\n",
//            (int)(result.bits[3] - MINUS * (result.bits[3] / MINUS)) /
//            65536);
//   }
//   printf("%d\n", error);
//   return 0;
// }