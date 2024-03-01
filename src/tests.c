#define _GNU_SOURCE
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(s21_from_decimal_to_float_test_1) {
  s21_decimal dec = {{1, 0, 0, 0}};
  // float res = 0;
  int error = s21_from_decimal_to_float(dec, NULL);
  ck_assert_int_eq(error, convertation_error);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_2) {
  s21_decimal dec = {{65468, 0, 0, 4 * pow(2, 16)}};
  float res = 6.5468;
  float tmp_res = 0;
  int error = s21_from_decimal_to_float(dec, &tmp_res);
  ck_assert_float_eq(res, tmp_res);
  ck_assert_int_eq(error, convertation_ok);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_3) {
  s21_decimal dec = {{387946, 0, 0, MINUS + 3 * pow(2, 16)}};
  float res = -387.946;
  float tmp_res = 0;
  s21_set_scale(&dec.bits[3], 3);
  dec.bits[3] = s21_set_bit_1(dec.bits[3], 31);
  int error = s21_from_decimal_to_float(dec, &tmp_res);
  ck_assert_float_eq(res, tmp_res);
  ck_assert_int_eq(error, convertation_ok);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_4) {
  s21_decimal dec = {{9768050, 0, 0, 5 * pow(2, 16)}};
  float res = 97.68050;
  float tmp_res = 0;
  s21_set_scale(&dec.bits[3], 5);
  int error = s21_from_decimal_to_float(dec, &tmp_res);
  ck_assert_float_eq(res, tmp_res);
  ck_assert_int_eq(error, convertation_ok);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_1) {
  s21_decimal dec = {{1234, 0, 0, 0}};
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(dec, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  s21_decimal dec = {{12345, 0, 0, 0}};
  dec.bits[3] = s21_set_bit_1(dec.bits[3], 31);
  int res = -12345;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(dec, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int value = 0;
  s21_from_int_to_decimal(5, &dec);
  s21_from_decimal_to_int(dec, &value);
  ck_assert_int_eq(5, value);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  s21_decimal dec = {{123451234, 0, 0, 0}};
  int res = 0;
  int number = 0;
  res = s21_from_decimal_to_int(dec, &number);
  ck_assert_int_eq(number, 123451234);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_1) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(0, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_init_decimal(&dec);
  s21_from_int_to_decimal(-128, &dec);
  ck_assert_int_eq(dec.bits[0], 128);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_3) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_init_decimal(&dec);
  s21_from_int_to_decimal(127, &dec);
  ck_assert_int_eq(dec.bits[0], 127);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_init_decimal(&dec);
  s21_from_int_to_decimal(-2147483648, &dec);
  ck_assert_int_eq(dec.bits[0], 2147483648);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_5) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_init_decimal(&dec);
  s21_from_int_to_decimal(2147483647, &dec);
  ck_assert_int_eq(dec.bits[0], 2147483647);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_1) {
  s21_decimal dec = {{0, 0, 0, 0}};
  float num = -2147483648;
  s21_from_float_to_decimal(num, &dec);
  ck_assert_int_eq(dec.bits[0], 2147483648);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_2) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_init_decimal(&dec);
  s21_from_float_to_decimal(10200000, &dec);
  ck_assert_int_eq(dec.bits[0], 10200000);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_3) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_init_decimal(&dec);
  s21_from_float_to_decimal(1e-30, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_1) {
  s21_decimal dec = {{1, 0, 0, MINUS}};
  s21_decimal res = {{1, 0, 0, MINUS}};
  int error = 0;
  error = s21_truncate(dec, &dec);
  ck_assert_int_eq(dec.bits[0], res.bits[0]);
  ck_assert_int_eq(dec.bits[1], res.bits[1]);
  ck_assert_int_eq(dec.bits[2], res.bits[2]);
  ck_assert_int_eq(dec.bits[3], res.bits[3]);
  ck_assert_int_eq(error, convertation_ok);
}
END_TEST

START_TEST(s21_truncate_test_2) {
  s21_decimal dec = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int error = s21_truncate(dec, &dec);
  ck_assert_int_eq(dec.bits[0], res.bits[0]);
  ck_assert_int_eq(dec.bits[1], res.bits[1]);
  ck_assert_int_eq(dec.bits[2], res.bits[2]);
  ck_assert_int_eq(dec.bits[3], res.bits[3]);
  ck_assert_int_eq(error, convertation_ok);
}
END_TEST

START_TEST(s21_truncate_test_3) {
  s21_decimal dec = {{1454, 0, 0, 3 * pow(2, 16)}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = s21_truncate(dec, &dec);
  ck_assert_int_eq(dec.bits[0], res.bits[0]);
  ck_assert_int_eq(dec.bits[1], res.bits[1]);
  ck_assert_int_eq(dec.bits[2], res.bits[2]);
  ck_assert_int_eq(dec.bits[3], res.bits[3]);
  ck_assert_int_eq(error, convertation_ok);
}
END_TEST

START_TEST(s21_truncate_test_4) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int error = s21_truncate(dec, NULL);
  ck_assert_int_eq(error, convertation_error);
}
END_TEST

START_TEST(s21_floor_test_1) {
  s21_decimal num = {{15, 0, 0, 1 * pow(2, 16)}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_floor_test_2) {
  s21_decimal num = {{19, 0, 0, 65536}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_floor_test_3) {
  s21_decimal num = {{155, 0, 0, 131072}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_floor_test_4) {
  s21_decimal num = {{0, 0, 0, 0}};
  int error = 0;
  error = s21_floor(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_floor_test_5) {
  s21_decimal num = {{21, 0, 0, MINUS}};
  s21_decimal res = {{3, 0, 0, MINUS}};
  s21_set_scale(&num.bits[3], 1);
  int error = 0;
  error = s21_floor(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_test_1) {
  s21_decimal num = {{15, 0, 0, pow(2, 16)}};
  s21_decimal res = {{2, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal num = {{149, 0, 0, 131072}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal num = {{35, 0, 0, 65536}};
  s21_decimal res = {{4, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_test_4) {
  s21_decimal num = {{251, 0, 0, 131072}};
  s21_decimal res = {{3, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_round_test_5) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_round(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_negate_test_1) {
  s21_decimal num = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_negate_test_2) {
  s21_decimal num = {{1, 0, 0, MINUS}};
  s21_decimal res = {{1, 0, 0, 0}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_negate_test_3) {
  s21_decimal num = {{1, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, MINUS}};
  int error = 0;
  error = s21_negate(num, &num);
  ck_assert_int_eq(num.bits[0], res.bits[0]);
  ck_assert_int_eq(num.bits[1], res.bits[1]);
  ck_assert_int_eq(num.bits[2], res.bits[2]);
  ck_assert_int_eq(num.bits[3], res.bits[3]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_is_equal_test_1) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_2) {
  s21_decimal x = {{0, 1, 0, MINUS}};
  s21_decimal y = {{0, 1, 0, MINUS}};
  int res = s21_is_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_4) {
  s21_decimal x = {{0, 127, 2, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_5) {
  s21_decimal x = {{0, 0, 2, 0}};
  s21_decimal y = {{65, 0, 0, 0}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_6) {
  s21_decimal x = {{0, 0, 2, MINUS}};
  s21_decimal y = {{65, 0, 0, 0}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_7) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, MINUS}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_8) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, MINUS}};
  int res = s21_is_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_9) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_10) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_11) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_12) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int res = s21_is_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_equal_test_13) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_greater_or_equal(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_greater_or_equal(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_5) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_6) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_greater_or_equal(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_7) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_greater_or_equal(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_8) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_9) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_10) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_11) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_12) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_or_equal_test_13) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int res = s21_is_greater_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int res = s21_is_greater(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_greater(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_greater(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_greater(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_5) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_greater(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_6) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_greater(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_7) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_greater(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_8) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_greater(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_9) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_greater(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_10) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_greater(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_11) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_greater(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_12) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int res = s21_is_greater(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_greater_test_13) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int res = s21_is_greater(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int res = s21_is_not_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_not_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_3) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_not_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_5) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_6) {
  s21_decimal x = {{0, 52, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_7) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_8) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{1747, 0, 1, 0}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_9) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_10) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_11) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_not_equal_test_12) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int res = s21_is_not_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_2) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_less_or_equal(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_less_or_equal(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_5) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_6) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_less_or_equal(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_7) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_less_or_equal(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_8) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_9) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_10) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_11) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_12) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_or_equal_test_13) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int res = s21_is_less_or_equal(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_1) {
  s21_decimal x = {{1, 2, 3, 917504}};
  s21_decimal y = {{1, 2, 3, 917504}};
  int res = s21_is_less(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_2) {
  s21_decimal x = {{4294967295, 0, 0, 0}};
  s21_decimal y = {{0, 1, 0, 0}};
  int res = s21_is_less(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_3) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 2, 0}};
  int res = s21_is_less(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_4) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_less(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_5) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_less(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_6) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 2, MINUS}};
  int res = s21_is_less(y, x);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_7) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_less(y, x);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_8) {
  s21_decimal x = {{0, 0, 1, MINUS}};
  s21_decimal y = {{0, 0, 1, 0}};
  int res = s21_is_less(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_9) {
  s21_decimal x = {{0, 0, 1, 0}};
  s21_decimal y = {{0, 0, 1, MINUS}};
  int res = s21_is_less(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_10) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_less(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_11) {
  s21_decimal x = {{1, 2, 3, -2146828288}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  int res = s21_is_less(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_12) {
  s21_decimal x = {{1, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, -2146959360}};
  int res = s21_is_less(x, y);
  int res_ = 0;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_is_less_test_13) {
  s21_decimal x = {{10, 2, 3, -2146566144}};
  s21_decimal y = {{3, 2, 1, 524288}};
  int res = s21_is_less(x, y);
  int res_ = 1;
  ck_assert_int_eq(res, res_);
}
END_TEST

START_TEST(s21_add_test_1) {
  s21_decimal bits1 = {{20, 0, 0, 1 * pow(2, 16)}};
  s21_decimal bits2 = {{11, 0, 0, 1 * pow(2, 16)}}, result;
  int error = s21_add(bits1, bits2, &result);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 3.1);
}
END_TEST

START_TEST(s21_add_test_2) {
  s21_decimal bits1 = {{20, 0, 0, 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_add(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 0);
}
END_TEST

START_TEST(s21_add_test_3) {
  s21_decimal bits1 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_add(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 0);
}
END_TEST

START_TEST(s21_add_test_4) {
  s21_decimal bits1 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_add(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, -4);
}
END_TEST

START_TEST(s21_add_test_5) {
  s21_decimal bits1 = {{20, 0, 0, 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, 2 * pow(2, 16)}}, result;
  float dst;
  int error = s21_add(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 2.2);
}
END_TEST

START_TEST(s21_add_test_6) {
  s21_decimal bits1 = {{0, 0, MINUS, 0}};
  s21_decimal bits2 = {{0, 0, MINUS, 0}}, result;
  int error = s21_add(bits1, bits2, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_add_test_7) {
  s21_decimal bits1 = {{0, 0, MINUS, MINUS}};
  s21_decimal bits2 = {{0, 0, MINUS, MINUS}}, result;
  int error = s21_add(bits1, bits2, &result);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(s21_sub_test_1) {
  s21_decimal bits1 = {{20, 0, 0, 1 * pow(2, 16)}};
  s21_decimal bits2 = {{11, 0, 0, 1 * pow(2, 16)}}, result;
  int error = s21_sub(bits1, bits2, &result);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 0.9);
}
END_TEST

START_TEST(s21_sub_test_2) {
  s21_decimal bits1 = {{20, 0, 0, 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_sub(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 4);
}
END_TEST

START_TEST(s21_sub_test_3) {
  s21_decimal bits1 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_sub(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, -4);
}
END_TEST

START_TEST(s21_sub_test_4) {
  s21_decimal bits1 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, MINUS + 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_sub(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, 0);
}
END_TEST

START_TEST(s21_sub_test_5) {
  s21_decimal bits1 = {{20, 0, 0, 2 * pow(2, 16)}};
  s21_decimal bits2 = {{20, 0, 0, 1 * pow(2, 16)}}, result;
  float dst;
  int error = s21_sub(bits1, bits2, &result);
  s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(dst, -1.8);
}
END_TEST

START_TEST(s21_sub_test_6) {
  s21_decimal bits1 = {{0, 0, MINUS, 0}};
  s21_decimal bits2 = {{0, 0, MINUS, MINUS}}, result;
  int error = s21_sub(bits1, bits2, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_sub_test_7) {
  s21_decimal bits1 = {{0, 0, MINUS, MINUS}};
  s21_decimal bits2 = {{0, 0, MINUS, 0}}, result;
  int error = s21_sub(bits1, bits2, &result);
  ck_assert_int_eq(error, 2);
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *suite;
  suite = suite_create("s21_decimal");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_1);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_2);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_3);
  tcase_add_test(tcase_core, s21_from_decimal_to_float_test_4);

  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_1);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_2);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_3);
  tcase_add_test(tcase_core, s21_from_decimal_to_int_test_4);

  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_1);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_2);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_3);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_4);
  tcase_add_test(tcase_core, s21_from_int_to_decimal_test_5);

  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_1);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_2);
  tcase_add_test(tcase_core, s21_from_float_to_decimal_test_3);

  tcase_add_test(tcase_core, s21_truncate_test_1);
  tcase_add_test(tcase_core, s21_truncate_test_2);
  tcase_add_test(tcase_core, s21_truncate_test_3);
  tcase_add_test(tcase_core, s21_truncate_test_4);

  tcase_add_test(tcase_core, s21_floor_test_1);
  tcase_add_test(tcase_core, s21_floor_test_2);
  tcase_add_test(tcase_core, s21_floor_test_3);
  tcase_add_test(tcase_core, s21_floor_test_4);
  tcase_add_test(tcase_core, s21_floor_test_5);

  tcase_add_test(tcase_core, s21_round_test_1);
  tcase_add_test(tcase_core, s21_round_test_2);
  tcase_add_test(tcase_core, s21_round_test_3);
  tcase_add_test(tcase_core, s21_round_test_4);
  tcase_add_test(tcase_core, s21_round_test_5);

  tcase_add_test(tcase_core, s21_negate_test_1);
  tcase_add_test(tcase_core, s21_negate_test_2);
  tcase_add_test(tcase_core, s21_negate_test_3);

  tcase_add_test(tcase_core, s21_is_equal_test_1);
  tcase_add_test(tcase_core, s21_is_equal_test_2);
  tcase_add_test(tcase_core, s21_is_equal_test_3);
  tcase_add_test(tcase_core, s21_is_equal_test_4);
  tcase_add_test(tcase_core, s21_is_equal_test_5);
  tcase_add_test(tcase_core, s21_is_equal_test_6);
  tcase_add_test(tcase_core, s21_is_equal_test_7);
  tcase_add_test(tcase_core, s21_is_equal_test_8);
  tcase_add_test(tcase_core, s21_is_equal_test_9);
  tcase_add_test(tcase_core, s21_is_equal_test_10);
  tcase_add_test(tcase_core, s21_is_equal_test_11);
  tcase_add_test(tcase_core, s21_is_equal_test_12);
  tcase_add_test(tcase_core, s21_is_equal_test_13);

  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_1);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_2);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_3);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_4);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_5);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_6);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_7);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_8);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_9);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_10);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_11);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_12);
  tcase_add_test(tcase_core, s21_is_greater_or_equal_test_13);

  tcase_add_test(tcase_core, s21_is_greater_test_1);
  tcase_add_test(tcase_core, s21_is_greater_test_2);
  tcase_add_test(tcase_core, s21_is_greater_test_3);
  tcase_add_test(tcase_core, s21_is_greater_test_4);
  tcase_add_test(tcase_core, s21_is_greater_test_5);
  tcase_add_test(tcase_core, s21_is_greater_test_6);
  tcase_add_test(tcase_core, s21_is_greater_test_7);
  tcase_add_test(tcase_core, s21_is_greater_test_8);
  tcase_add_test(tcase_core, s21_is_greater_test_9);
  tcase_add_test(tcase_core, s21_is_greater_test_10);
  tcase_add_test(tcase_core, s21_is_greater_test_11);
  tcase_add_test(tcase_core, s21_is_greater_test_12);
  tcase_add_test(tcase_core, s21_is_greater_test_13);

  tcase_add_test(tcase_core, s21_is_not_equal_test_1);
  tcase_add_test(tcase_core, s21_is_not_equal_test_2);
  tcase_add_test(tcase_core, s21_is_not_equal_test_3);
  tcase_add_test(tcase_core, s21_is_not_equal_test_4);
  tcase_add_test(tcase_core, s21_is_not_equal_test_5);
  tcase_add_test(tcase_core, s21_is_not_equal_test_6);
  tcase_add_test(tcase_core, s21_is_not_equal_test_7);
  tcase_add_test(tcase_core, s21_is_not_equal_test_8);
  tcase_add_test(tcase_core, s21_is_not_equal_test_9);
  tcase_add_test(tcase_core, s21_is_not_equal_test_10);
  tcase_add_test(tcase_core, s21_is_not_equal_test_11);
  tcase_add_test(tcase_core, s21_is_not_equal_test_12);

  tcase_add_test(tcase_core, s21_is_less_or_equal_test_1);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_2);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_3);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_4);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_5);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_6);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_7);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_8);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_9);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_10);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_11);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_12);
  tcase_add_test(tcase_core, s21_is_less_or_equal_test_13);

  tcase_add_test(tcase_core, s21_is_less_test_1);
  tcase_add_test(tcase_core, s21_is_less_test_2);
  tcase_add_test(tcase_core, s21_is_less_test_3);
  tcase_add_test(tcase_core, s21_is_less_test_4);
  tcase_add_test(tcase_core, s21_is_less_test_5);
  tcase_add_test(tcase_core, s21_is_less_test_6);
  tcase_add_test(tcase_core, s21_is_less_test_7);
  tcase_add_test(tcase_core, s21_is_less_test_8);
  tcase_add_test(tcase_core, s21_is_less_test_9);
  tcase_add_test(tcase_core, s21_is_less_test_10);
  tcase_add_test(tcase_core, s21_is_less_test_11);
  tcase_add_test(tcase_core, s21_is_less_test_12);
  tcase_add_test(tcase_core, s21_is_less_test_13);

  tcase_add_test(tcase_core, s21_add_test_1);
  tcase_add_test(tcase_core, s21_add_test_2);
  tcase_add_test(tcase_core, s21_add_test_3);
  tcase_add_test(tcase_core, s21_add_test_4);
  tcase_add_test(tcase_core, s21_add_test_5);
  tcase_add_test(tcase_core, s21_add_test_6);
  tcase_add_test(tcase_core, s21_add_test_7);

  tcase_add_test(tcase_core, s21_sub_test_1);
  tcase_add_test(tcase_core, s21_sub_test_2);
  tcase_add_test(tcase_core, s21_sub_test_3);
  tcase_add_test(tcase_core, s21_sub_test_4);
  tcase_add_test(tcase_core, s21_sub_test_5);
  tcase_add_test(tcase_core, s21_sub_test_6);
  tcase_add_test(tcase_core, s21_sub_test_7);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_string_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}