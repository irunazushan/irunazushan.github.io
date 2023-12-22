#include "s21_decimal.h"

void copy_decimal(s21_decimal src, s21_decimal *dst) {
  reset(dst);
  for (int i = 0; i < 96; i++) set_bit(dst, i, get_bit(src, i));
  set_scale(dst, get_scale(src));
  set_sign(dst, get_sign(src));
}

int first_bit(s21_decimal src) {
  int index = 0;
  int i = 95;
  for (; i >= 0 && get_bit(src, i) == 0; i--)
    ;
  if (get_bit(src, i) == 1) index = i;
  return index;
}

int is_full_mantis(s21_decimal src) {
  s21_decimal full_dec = {{0, 0, 0, 0}};
  for (int i = 0; i < 96; i++) set_bit(&full_dec, i, 1);
  return s21_is_equal(src, full_dec);
}

int is_empty_mantis(s21_decimal src) {
  int is_empty = 1;
  int i = 0;
  for (; i < 3 && src.bits[i] == 0; i++)
    ;
  if (src.bits[i] != 0) is_empty = 0;
  return is_empty;
}

int is_greater_abs(s21_decimal value_1, s21_decimal value_2) {
  int is_greater = 0;
  int i = 95;
  for (; i >= 0 && get_bit(value_1, i) - get_bit(value_2, i) == 0; i--)
    ;
  if (get_bit(value_1, i) - get_bit(value_2, i) == 1) is_greater = 1;
  return is_greater;
}

int add_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if ((!is_empty_mantis(value_2) && is_full_mantis(value_1)) ||
      (is_full_mantis(value_2) && !is_empty_mantis(value_1)))
    return 1;
  else {
    int temp = 0;
    for (int i = 0; i < 96; i++) {
      int sum = get_bit(value_1, i) + get_bit(value_2, i) + temp;
      if (sum == 0) set_bit(result, i, 0);
      if (sum == 1) {
        set_bit(result, i, 1);
        temp = 0;
      }
      if (sum == 2) {
        set_bit(result, i, 0);
        temp = 1;
      }
      if (sum == 3) {
        set_bit(result, i, 1);
        temp = 1;
      }
      if (i == 95 && temp) error = 1;
    }
  }
  return error;
}

void scale_increase(s21_decimal *less_val, int *scale_less) {
  s21_decimal temp_dec1;
  s21_decimal temp_dec2;
  copy_decimal(*less_val, &temp_dec1);
  copy_decimal(*less_val, &temp_dec2);
  set_scale(&temp_dec1, 0);
  set_scale(&temp_dec2, 0);
  left_shift(&temp_dec1, 3);
  left_shift(&temp_dec2, 1);
  add_bits(temp_dec1, temp_dec2, less_val);
  (*scale_less)++;
}

void scale_decrease(s21_decimal *greater_val, int *scale_gteater, int div) {
  s21_decimal temp_dec1;
  s21_decimal temp_dec2;
  s21_decimal reminder;
  reset(&reminder);
  reset(&temp_dec2);
  temp_dec2.bits[0] = pow(10, div);
  copy_decimal(*greater_val, &temp_dec1);
  int sign = get_sign(*greater_val);
  set_scale(&temp_dec1, 0);
  set_sign(&temp_dec1, 0);
  div_with_remainder(temp_dec1, temp_dec2, greater_val, &reminder);
  (*scale_gteater) -= div;
  set_scale(greater_val, *scale_gteater);
  set_sign(greater_val, sign);
}

void equal_scale(s21_decimal *val1, s21_decimal *val2) {
  s21_decimal *greater_val = val1;
  s21_decimal *less_val = val2;
  int scale_gteater = get_scale(*val1);
  int scale_less = get_scale(*val2);

  if (scale_less > scale_gteater) {
    greater_val = val2;
    less_val = val1;
    scale_gteater = get_scale(*val2);
    scale_less = get_scale(*val1);
  }
  int scale_diff = scale_gteater - scale_less;
  int i = 0;
  for (; i < scale_diff && first_bit(*less_val) + 4 < 96; i++) {
    scale_increase(less_val, &scale_less);
  }
  set_scale(less_val, scale_less);

  if (first_bit(*less_val) + 4 >= 96) {
    int div = scale_diff - i;
    scale_decrease(greater_val, &scale_gteater, div);
  }
}

int sub_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int temp = 0;
  for (int i = 0; i < 96; i++) {
    int sub = 0;
    if (is_greater_abs(value_2, value_1))
      sub = get_bit(value_2, i) - get_bit(value_1, i) - temp;
    else
      sub = get_bit(value_1, i) - get_bit(value_2, i) - temp;
    if (sub == 0) {
      set_bit(result, i, 0);
      temp = 0;
    }
    if (sub == 1) set_bit(result, i, 1);
    if (sub == -1) {
      set_bit(result, i, 1);
      temp = 1;
    }
    if (sub == -2) {
      set_bit(result, i, 0);
      temp = 1;
    }
  }
  return 0;
}

void copy_mantis(s21_decimal src, s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  for (int i = 0; i < 96; i++) set_bit(dst, i, get_bit(src, i));
}

s21_decimal div_10(s21_decimal *val) {
  s21_decimal value_dec = {{0, 0, 0, 0}};
  s21_decimal dec_10 = {{0, 0, 0, 0}};
  s21_decimal reminder = {{0, 0, 0, 0}};
  s21_decimal div_res = {{0, 0, 0, 0}};
  copy_mantis(*val, &value_dec);

  dec_10.bits[0] = 10;
  div_with_remainder(value_dec, dec_10, &div_res, &reminder);
  copy_mantis(div_res, val);
  set_scale(val, get_scale(*val) - 1);
  return reminder;
}

void add_1(s21_decimal *val) {
  s21_decimal value_dec = {{0, 0, 0, 0}};
  s21_decimal dec_1 = {{1, 0, 0, 0}};
  s21_decimal add_res = {{0, 0, 0, 0}};
  copy_mantis(*val, &value_dec);
  add_bits(value_dec, dec_1, &add_res);
  copy_mantis(add_res, val);
}

void round_for_add(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result, s21_decimal val1, s21_decimal val2) {
  s21_decimal value_dec = {{0, 0, 0, 0}};
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(val1);
  if (get_scale(val1) > get_scale(val2))
    copy_decimal(value_1, &value_dec);
  else {
    copy_decimal(value_2, &value_dec);
    scale1 = get_scale(value_2);
    scale2 = get_scale(val2);
  }
  int div = (scale1 - scale2) - 1;
  scale_decrease(&value_dec, &scale1, div);
  s21_decimal dec_1 = {{0, 0, 0, 0}};
  dec_1.bits[0] = 1;
  s21_decimal dec_10 = {{0, 0, 0, 0}};
  s21_decimal reminder = {{0, 0, 0, 0}};
  s21_decimal div_res = {{0, 0, 0, 0}};
  dec_10.bits[0] = 10;
  set_scale(&value_dec, 0);
  set_sign(&value_dec, 0);
  div_with_remainder(value_dec, dec_10, &div_res, &reminder);
  int remaind = reminder.bits[0];
  if (get_sign(val1) == get_sign(val2) &&
      (remaind > 5 || (remaind == 5 && get_bit(*result, 0) == 1)))
    add_1(result);
  else if (remaind > 5 || (remaind == 5 && get_bit(*result, 0) == 1))
    sub_bits(*result, dec_1, result);
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset(result);
  int error = 0;
  int round = 0;
  s21_decimal val1 = {{0, 0, 0, 0}};
  copy_decimal(value_1, &val1);
  s21_decimal val2 = {{0, 0, 0, 0}};
  copy_decimal(value_2, &val2);
  int sign_result = 0;
  if (get_scale(value_1) != get_scale(value_2)) equal_scale(&val1, &val2);
  if ((first_bit(val1) == 95 && get_scale(val1) != 0) ||
      (first_bit(val2) == 95 && get_scale(val2) != 0)) {
    s21_decimal add_res = {{0, 0, 0, 0}};

    if (get_sign(val1) == get_sign(val2)) {
      add_bits(div_10(&val1), div_10(&val2), &add_res);
      round = add_res.bits[0];
    } else {
      sub_bits(div_10(&val1), div_10(&val2), &add_res);
      round = add_res.bits[0];
    }
  }
  int scale = get_scale(val1);
  if (get_sign(val1) == get_sign(val2)) {
    sign_result = get_sign(val1);
    error = add_bits(val1, val2, result);
    set_sign(result, sign_result);
    if (error && sign_result) error = 2;
  } else {
    if ((get_sign(val1) == 1 && is_greater_abs(val1, val2)) ||
        (get_sign(val2) == 1 && is_greater_abs(val2, val1)))
      sign_result = 1;
    sub_bits(val1, val2, result);
    set_sign(result, sign_result);
  }
  set_scale(result, scale);
  if (round >= 10) add_1(result);
  if ((((round > 5 && round <= 9) || round > 15) ||
       ((round == 5 || round == 15) && get_bit(*result, 0) == 1)) &&
      get_sign(val1) == get_sign(val2))
    add_1(result);
  else if (!round &&
           (is_greater_abs(value_1, val1) || is_greater_abs(value_2, val2))) {
    round_for_add(value_1, value_2, result, val1, val2);
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign = 1 - get_sign(value_2);
  s21_decimal dec_num = {{0, 0, 0, 0}};
  copy_decimal(value_2, &dec_num);
  set_sign(&dec_num, sign);
  s21_add(value_1, dec_num, result);
  return 0;
}

int is_end_of_div(s21_decimal val2, s21_decimal *result, s21_decimal *sub_res,
                  s21_decimal *tmp2) {
  int break_flag = 0;
  sub_bits(*sub_res, *tmp2, sub_res);
  left_shift(result, 1);
  set_bit(result, 0, 1);
  if (s21_is_greater(*tmp2, val2) && s21_is_less(*sub_res, val2)) {
    while (!s21_is_equal(*tmp2, val2)) {
      right_shift(tmp2, 1);
      left_shift(result, 1);
    }
    break_flag = 1;
  } else if (s21_is_greater(*tmp2, val2) && s21_is_equal(*sub_res, val2)) {
    while (!s21_is_equal(*tmp2, val2)) {
      right_shift(tmp2, 1);
      left_shift(result, 1);
    }
    set_bit(result, 0, 1);
    break_flag = 1;
  } else if (s21_is_equal(*sub_res, val2)) {
    left_shift(result, 1);
    set_bit(result, 0, 1);
    break_flag = 1;
  } else if (s21_is_less(*sub_res, val2))
    break_flag = 1;
  else
    right_shift(tmp2, 1);
  return break_flag;
}

int div_with_remainder(s21_decimal val1, s21_decimal val2, s21_decimal *result,
                       s21_decimal *reminder) {
  reset(result);
  s21_decimal zero_dec = {{0, 0, 0, 0}};
  int error = 0;
  if (s21_is_equal(val2, zero_dec))
    error = 3;
  else {
    int bexp1 = get_binexp_from_decimal(val1);
    int bexp2 = get_binexp_from_decimal(val2);
    int diff = bexp1 - bexp2;
    int break_flag = 0;
    s21_decimal tmp2 = val2;
    s21_decimal sub_res = val1;
    left_shift(&tmp2, diff);
    while (s21_is_greater_or_equal(sub_res, val2) && !break_flag) {
      if (s21_is_greater(tmp2, sub_res)) {
        left_shift(result, 1);
        right_shift(&tmp2, 1);
      } else
        break_flag = is_end_of_div(val2, result, &sub_res, &tmp2);
    }
    *reminder = sub_res;
  }
  return error;
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  reset(result);
  int error_status = DEC_OK;
  big_decimal tmp = {{0, 0, 0, 0, 0, 0, 0}};
  big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0}};
  int tmp_arg;
  int exp1 = get_binexp_from_decimal(value_1);
  int exp2 = get_binexp_from_decimal(value_2);
  for (int i = 0; i <= exp2 && error_status == DEC_OK; i++) {
    tmp_arg = get_bit(value_2, i);
    for (int j = 0; j <= exp1; j++) {
      big_set_bit(&tmp, j + i, get_bit(value_1, j) * tmp_arg);
    }
    error_status = big_add_bits(big_result, tmp, &big_result);
    tmp = (big_decimal){{0, 0, 0, 0, 0, 0}};
  }
  int scale = (get_scale(value_1) + get_scale(value_2));
  int sign = (get_sign(value_1) ^ get_sign(value_2));
  error_status = big_to_dec(big_result, result, scale);
  if (error_status && sign) error_status = DEC_SMALL;
  set_sign(result, (get_sign(value_1) ^ get_sign(value_2)));
  return error_status;
}

int s21_div(s21_decimal val1, s21_decimal val2, s21_decimal *result) {
  int error_status = DEC_OK;
  if (val2.bits[2] == 0 && val2.bits[1] == 0 && val2.bits[0] == 0) {
    error_status = DEC_DIV_BY_ZERO;
  } else {
    reset(result);
    big_decimal big_val1 = dec_to_big(val1);
    big_decimal big_val2 = dec_to_big(val2);
    big_decimal big_res = {{0, 0, 0, 0, 0, 0, 0}};
    big_decimal big_rem = {{0, 0, 0, 0, 0, 0, 0}};
    int scale1 = get_scale(val1);
    int scale2 = get_scale(val2);
    int gen_scale = scale1 - scale2;
    big_up_precision(&gen_scale, &big_val1);
    big_div_with_remainder(big_val1, big_val2, &big_res, &big_rem);
    error_status = big_to_dec(big_res, result, gen_scale);
    int sign = (get_sign(val1) ^ get_sign(val2));
    if (error_status && sign) error_status = DEC_SMALL;
    set_sign(result, sign);
  }
  return error_status;
}