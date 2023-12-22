#include "s21_decimal.h"

void scale_decrease2(s21_decimal *greater_val, int *scale_gteater, int div) {
  s21_decimal temp_dec1;
  s21_decimal temp_dec2;
  s21_decimal reminder;
  reset(&reminder);
  reset(&temp_dec2);
  float mantissa = powf(10.0, (float)div);
  setMantissaF(&temp_dec2, mantissa);
  copy_decimal(*greater_val, &temp_dec1);
  int sign = get_sign(*greater_val);
  set_scale(&temp_dec1, 0);
  set_sign(&temp_dec1, 0);
  div_with_remainder(temp_dec1, temp_dec2, greater_val, &reminder);
  (*scale_gteater) -= div;
  set_scale(greater_val, *scale_gteater);
  set_sign(greater_val, sign);
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = DEC_OK;
  copy_decimal(value, result);
  int scale = get_scale(*result);
  if (scale > 0 && !get_sign(*result))
    scale_decrease2(result, &scale, get_scale(*result));
  else if (scale > 0 && get_sign(*result)) {
    scale_decrease2(result, &scale, get_scale(*result) - 1);
    s21_decimal value_dec = {{0, 0, 0, 0}};
    s21_decimal dec_10 = {{10, 0, 0, 0}};
    s21_decimal reminder = {{0, 0, 0, 0}};
    s21_decimal div_res = {{0, 0, 0, 0}};
    copy_mantis(*result, &value_dec);
    div_with_remainder(value_dec, dec_10, &div_res, &reminder);
    div_10(result);
    int remaind = reminder.bits[0];
    if (remaind > 0 && remaind < 10 && get_sign(*result)) add_1(result);
  }
  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = DEC_OK;
  copy_decimal(value, result);
  int scale = get_scale(*result);
  if (scale > 0) {
    scale_decrease2(result, &scale, get_scale(*result) - 1);
    s21_decimal value_dec = {{0, 0, 0, 0}};
    s21_decimal dec_10 = {{10, 0, 0, 0}};
    s21_decimal reminder = {{0, 0, 0, 0}};
    s21_decimal div_res = {{0, 0, 0, 0}};
    copy_mantis(*result, &value_dec);
    div_with_remainder(value_dec, dec_10, &div_res, &reminder);
    div_10(result);
    int remaind = reminder.bits[0];
    if (remaind > 4 && remaind < 10) add_1(result);
  }
  return res;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = DEC_OK;
  copy_decimal(value, result);
  int scale = get_scale(*result);
  if (scale > 0) scale_decrease2(result, &scale, get_scale(*result));
  return res;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = DEC_OK;

  reset(result);

  int sign = 1 - get_sign(value);
  int scale = get_scale(value);

  set_sign(result, sign);
  set_scale(result, scale);

  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }

  return res;
}
