#include "s21_decimal.h"

void big_set_bit(big_decimal *dst, int shift, int bit) {
  int shift_int = 1;
  int bits_numb = shift / 32;
  int index_numb = shift % 32;
  if (bit)
    dst->bits[bits_numb] = dst->bits[bits_numb] | shift_int << index_numb;
  else
    dst->bits[bits_numb] = dst->bits[bits_numb] & ~(shift_int << index_numb);
}

int big_get_bit(big_decimal src, int shift) {
  int bit = 0;
  int shift_int = 1;
  int bits_numb = shift / 32;
  int index_numb = shift % 32;
  if ((src.bits[bits_numb] & shift_int << index_numb) != 0) bit = 1;
  return bit;
}

int big_add_bits(big_decimal value_1, big_decimal value_2,
                 big_decimal *result) {
  int error = 0;
  int temp = 0;
  for (int i = 0; i < 192; i++) {
    int sum = big_get_bit(value_1, i) + big_get_bit(value_2, i) + temp;
    if (sum == 0) big_set_bit(result, i, 0);
    if (sum == 1) {
      big_set_bit(result, i, 1);
      temp = 0;
    }
    if (sum == 2) {
      big_set_bit(result, i, 0);
      temp = 1;
    }
    if (sum == 3) {
      big_set_bit(result, i, 1);
      temp = 1;
    }
    if (i == 191 && temp) error = DEC_HUGE;
  }
  return error;
}

int get_binexp_from_big(big_decimal src) {
  int bin_exp = 191, bit = 0;
  while (!bit) {
    bit = big_get_bit(src, bin_exp--);
  }
  return bin_exp + 1;
}

int big_is_greater_abs(big_decimal value_1, big_decimal value_2) {
  int is_greater = 0;
  int i = 191;
  for (; i >= 0 && big_get_bit(value_1, i) - big_get_bit(value_2, i) == 0; i--)
    ;
  if (big_get_bit(value_1, i) - big_get_bit(value_2, i) == 1) is_greater = 1;
  return is_greater;
}

int big_is_equal_abs(big_decimal value_1, big_decimal value_2) {
  int is_equal = 1;
  for (int i = 191; i >= 0; i--) {
    if ((big_get_bit(value_1, i) - big_get_bit(value_2, i) != 0)) is_equal = 0;
  }
  return is_equal;
}

int big_sub_bits(big_decimal value_1, big_decimal value_2,
                 big_decimal *result) {
  int temp = 0;
  for (int i = 0; i < 192; i++) {
    int sub = 0;
    if (big_is_greater_abs(value_2, value_1))
      sub = big_get_bit(value_2, i) - big_get_bit(value_1, i) - temp;
    else
      sub = big_get_bit(value_1, i) - big_get_bit(value_2, i) - temp;
    if (sub == 0) {
      big_set_bit(result, i, 0);
      temp = 0;
    }
    if (sub == 1) big_set_bit(result, i, 1);
    if (sub == -1) {
      big_set_bit(result, i, 1);
      temp = 1;
    }
    if (sub == -2) {
      big_set_bit(result, i, 0);
      temp = 1;
    }
  }
  return 0;
}

void big_left_shift(big_decimal *dst, int shift) {
  if (shift > 192) shift = 192;
  for (int i = 0; i < shift; i++) {
    int bit_31 = big_get_bit(*dst, 31);
    int bit_63 = big_get_bit(*dst, 63);
    int bit_95 = big_get_bit(*dst, 95);
    int bit_127 = big_get_bit(*dst, 127);
    int bit_159 = big_get_bit(*dst, 159);
    for (int j = 0; j < 6; j++) dst->bits[j] <<= 1;
    big_set_bit(dst, 32, bit_31);
    big_set_bit(dst, 64, bit_63);
    big_set_bit(dst, 96, bit_95);
    big_set_bit(dst, 128, bit_127);
    big_set_bit(dst, 160, bit_159);
  }
}

void big_right_shift(big_decimal *dst, int shift) {
  if (shift > 192) shift = 192;
  for (int i = 0; i < shift; i++) {
    int bit_160 = big_get_bit(*dst, 160);
    int bit_128 = big_get_bit(*dst, 128);
    int bit_96 = big_get_bit(*dst, 96);
    int bit_64 = big_get_bit(*dst, 64);
    int bit_32 = big_get_bit(*dst, 32);
    for (int j = 0; j < 6; j++) dst->bits[j] >>= 1;
    big_set_bit(dst, 159, bit_160);
    big_set_bit(dst, 127, bit_128);
    big_set_bit(dst, 95, bit_96);
    big_set_bit(dst, 63, bit_64);
    big_set_bit(dst, 31, bit_32);
    if (shift == 191 && i == 0) big_set_bit(dst, 191, 0);
  }
}

void big_reset(big_decimal *dst) {
  for (int i = 0; i < 6; i++) {
    dst->bits[i] = 0;
  }
}

int big_is_end_of_div(big_decimal val2, big_decimal *result,
                      big_decimal *sub_res, big_decimal *tmp2) {
  int break_flag = 0;
  big_sub_bits(*sub_res, *tmp2, sub_res);
  big_left_shift(result, 1);
  big_set_bit(result, 0, 1);
  if (big_is_equal_abs(*sub_res, val2) && big_is_equal_abs(*sub_res, *tmp2)) {
    big_right_shift(result, 1);
    break_flag = 1;
  } else if (big_is_greater_abs(*tmp2, val2) &&
             big_is_greater_abs(val2, *sub_res)) {
    while (!big_is_equal_abs(*tmp2, val2)) {
      big_right_shift(tmp2, 1);
      big_left_shift(result, 1);
    }
    break_flag = 1;
  } else if (big_is_greater_abs(*tmp2, val2) &&
             big_is_equal_abs(*sub_res, val2)) {
    while (big_is_greater_abs(*tmp2, val2)) {
      big_right_shift(tmp2, 1);
      big_left_shift(result, 1);
    }
    big_set_bit(result, 0, 1);
    break_flag = 1;
  } else if (big_is_equal_abs(*sub_res, val2)) {
    big_left_shift(result, 1);
    big_set_bit(result, 0, 1);
    break_flag = 1;
  } else if (big_is_greater_abs(val2, *sub_res))
    break_flag = 1;
  else
    big_right_shift(tmp2, 1);
  return break_flag;
}

int big_div_with_remainder(big_decimal val1, big_decimal val2,
                           big_decimal *result, big_decimal *reminder) {
  big_reset(result);
  big_decimal zero_dec = {{0, 0, 0, 0, 0, 0, 0}};
  int error = 0;
  if (big_is_equal_abs(val2, zero_dec))
    error = 3;
  else {
    int bexp1 = get_binexp_from_big(val1);
    int bexp2 = get_binexp_from_big(val2);
    int diff = bexp1 - bexp2;
    int break_flag = 0;
    big_decimal tmp2 = val2;
    big_decimal sub_res = val1;
    big_left_shift(&tmp2, diff);
    while ((big_is_equal_abs(sub_res, val2) ||
            big_is_greater_abs(sub_res, val2)) &&
           !break_flag) {
      if (big_is_greater_abs(tmp2, sub_res) &&
          (big_is_greater_abs(tmp2, val2))) {
        big_left_shift(result, 1);
        big_right_shift(&tmp2, 1);
      } else {
        break_flag = big_is_end_of_div(val2, result, &sub_res, &tmp2);
      }
    }
    *reminder = sub_res;
  }
  return error;
}

void round_big_decimal(big_decimal *big_res, int rem) {
  big_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
  if ((rem == 5 && big_res->bits[0] & 1) || rem > 5) {
    big_add_bits(*big_res, one, big_res);
  }
}

int big_to_dec(big_decimal big_result, s21_decimal *result, int scale) {
  int error_status = DEC_OK;
  int big_exp = get_binexp_from_big(big_result);
  big_decimal big_ten = {{10, 0, 0, 0, 0, 0, 0}};
  big_decimal big_res = big_result;
  big_decimal big_rem = {{0, 0, 0, 0, 0, 0, 0}};
  big_decimal max_dec = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0, 0, 0, 0}};
  while (big_exp > 95 && error_status == DEC_OK) {
    big_div_with_remainder(big_res, big_ten, &big_res, &big_rem);
    scale--;
    big_exp = get_binexp_from_big(big_res);
    if (scale < 0) {
      error_status = DEC_HUGE;
    }
  }
  while (scale > 28) {
    big_div_with_remainder(big_res, big_ten, &big_res, &big_rem);
    scale--;
  }
  if (!big_is_equal_abs(big_res, max_dec))
    round_big_decimal(&big_res, big_rem.bits[0]);
  for (int i = 0; i < 3 && error_status == DEC_OK; i++) {
    result->bits[i] = big_res.bits[i];
  }
  set_scale(result, scale);
  return error_status;
}

int big_mul(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  big_reset(result);
  int error_status = DEC_OK;
  big_decimal tmp = {{0, 0, 0, 0, 0, 0, 0}};
  big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0}};
  int tmp_arg;
  int exp1 = get_binexp_from_big(value_1);
  int exp2 = get_binexp_from_big(value_2);
  for (int i = 0; i <= exp2 && error_status == DEC_OK; i++) {
    tmp_arg = big_get_bit(value_2, i);
    for (int j = 0; j <= exp1; j++) {
      big_set_bit(&tmp, j + i, big_get_bit(value_1, j) * tmp_arg);
    }
    error_status = big_add_bits(big_result, tmp, &big_result);
    tmp = (big_decimal){{0, 0, 0, 0, 0, 0}};
  }
  *result = big_result;
  return error_status;
}

void big_up_precision(int *gen_scale, big_decimal *value_1) {
  big_decimal tmp = *value_1;
  int binexp = 0;
  big_decimal ten = {{10, 0, 0, 0, 0, 0, 0}};
  while (binexp < 189 && *gen_scale < 55) {
    binexp = get_binexp_from_big(tmp);
    if (binexp < 189 && *gen_scale < 55) {
      *(gen_scale) += 1;
      big_mul(*value_1, ten, value_1);
      big_mul(*value_1, ten, &tmp);
    }
  }
}

big_decimal dec_to_big(s21_decimal dec) {
  big_decimal big_dec = {{0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    big_dec.bits[i] = dec.bits[i];
  }
  return big_dec;
}