#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_INT 2147483647
#define MIN_INT -2147483648

#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -79228162514264337593543950335.0F

#define DEC_ERROR 1

enum arithmetics_status { DEC_OK, DEC_HUGE, DEC_SMALL, DEC_DIV_BY_ZERO };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} big_decimal;

// auxiliary functions
void reset(s21_decimal *dst);
int get_bit(s21_decimal src, int shift);
void set_bit(s21_decimal *dst, int shift, int bit);
void left_shift(s21_decimal *dst, int shift);
void right_shift(s21_decimal *dst, int shift);
void set_sign(s21_decimal *dst, int sign);
int get_sign(s21_decimal src);
void equal_scale(s21_decimal *val1, s21_decimal *val2);
int set_scale(s21_decimal *dst, int scale);
int get_scale(s21_decimal src);
void scale_decrease(s21_decimal *greater_val, int *scale_gteater, int div);
void copy_decimal(s21_decimal src, s21_decimal *dst);
void copy_mantis(s21_decimal src, s21_decimal *dst);
int sub_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal div_10(s21_decimal *val);
void add_1(s21_decimal *val);

// convertors
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int get_binexp_from_decimal(s21_decimal src);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
float setMantissaF(s21_decimal *dst, float src);

// comparison
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

// arithmetics
void equal_scale(s21_decimal *val1, s21_decimal *val2);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int div_with_remainder(s21_decimal val1, s21_decimal val2, s21_decimal *result,
                       s21_decimal *reminder);
int s21_div(s21_decimal val1, s21_decimal val2, s21_decimal *result);

// another
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// big_section
void big_set_sign(big_decimal *dst, int sign);
int big_set_scale(big_decimal *dst, int scale);
int big_get_scale(big_decimal src);
void big_set_bit(big_decimal *dst, int shift, int bit);
int big_get_bit(big_decimal src, int shift);
int big_add_bits(big_decimal value_1, big_decimal value_2, big_decimal *result);
int get_binexp_from_big(big_decimal src);
int big_is_greater_abs(big_decimal value_1, big_decimal value_2);
int big_is_equal_abs(big_decimal value_1, big_decimal value_2);
int big_sub_bits(big_decimal value_1, big_decimal value_2, big_decimal *result);
void big_left_shift(big_decimal *dst, int shift);
void big_right_shift(big_decimal *dst, int shift);
int big_get_sign(big_decimal src);
void big_reset(big_decimal *dst);
int big_is_end_of_div(big_decimal val2, big_decimal *result,
                      big_decimal *sub_res, big_decimal *tmp2);
int big_div_with_remainder(big_decimal val1, big_decimal val2,
                           big_decimal *result, big_decimal *reminder);
void round_big_decimal(big_decimal *big_res, int rem);
int big_to_dec(big_decimal big_result, s21_decimal *result, int scale);
int big_mul(big_decimal value_1, big_decimal value_2, big_decimal *result);
void big_up_precision(int *gen_scale, big_decimal *value_1);
big_decimal dec_to_big(s21_decimal dec);
#endif
