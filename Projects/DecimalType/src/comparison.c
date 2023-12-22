#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int is_greater = 0;
  s21_decimal val1 = value_1;
  s21_decimal val2 = value_2;
  if (get_scale(value_1) != get_scale(value_2)) equal_scale(&val1, &val2);
  if (get_sign(val1) - get_sign(val2) == -1)
    is_greater = 1;
  else if (get_sign(val1) - get_sign(val2) == 1)
    is_greater = 0;
  else {
    int i = 95;
    for (; i >= 0 && get_bit(val1, i) - get_bit(val2, i) == 0; i--)
      ;
    if (get_bit(val1, i) - get_bit(val2, i) == 1) is_greater = 1;
    if (get_sign(val1) == 1) is_greater = !is_greater;
  }
  return is_greater;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_2, value_1);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int is_equal = 0;
  s21_decimal val1 = value_1;
  s21_decimal val2 = value_2;
  if (get_scale(value_1) != get_scale(value_2)) equal_scale(&val1, &val2);
  if (get_sign(val1) - get_sign(val2) == 0) {
    int i = 95;
    for (; i >= 0 && get_bit(val1, i) - get_bit(val2, i) == 0; i--)
      ;
    if (get_bit(val1, i) - get_bit(val2, i) == 0) is_equal = 1;
  }
  return is_equal;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int is_less_or_equal = 0;
  if (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2))
    is_less_or_equal = 1;
  return is_less_or_equal;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int is_greater_or_equal = 0;
  if (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2))
    is_greater_or_equal = 1;
  return is_greater_or_equal;
}
