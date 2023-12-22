#include "s21_decimal.h"

void reset(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

int get_bit(s21_decimal src, int shift) {
  int bit = 0;
  int shift_int = 1;
  int bits_numb = shift / 32;
  int index_numb = shift % 32;
  if ((src.bits[bits_numb] & shift_int << index_numb) != 0) bit = 1;
  return bit;
}

void set_bit(s21_decimal *dst, int shift, int bit) {
  int shift_int = 1;
  int bits_numb = shift / 32;
  int index_numb = shift % 32;
  if (bit)
    dst->bits[bits_numb] = dst->bits[bits_numb] | shift_int << index_numb;
  else
    dst->bits[bits_numb] = dst->bits[bits_numb] & ~(shift_int << index_numb);
}

void left_shift(s21_decimal *dst, int shift) {
  if (shift > 96) shift = 96;
  for (int i = 0; i < shift; i++) {
    int bit_31 = get_bit(*dst, 31);
    int bit_63 = get_bit(*dst, 63);
    for (int j = 0; j < 3; j++) dst->bits[j] <<= 1;
    set_bit(dst, 32, bit_31);
    set_bit(dst, 64, bit_63);
  }
}

void right_shift(s21_decimal *dst, int shift) {
  if (shift > 96) shift = 96;
  for (int i = 0; i < shift; i++) {
    int bit_64 = get_bit(*dst, 64);
    int bit_32 = get_bit(*dst, 32);
    for (int j = 0; j < 3; j++) dst->bits[j] >>= 1;
    set_bit(dst, 63, bit_64);
    set_bit(dst, 31, bit_32);
    if (shift == 95 && i == 0) set_bit(dst, 95, 0);
  }
}

void set_sign(s21_decimal *dst, int sign) {
  if (sign)
    dst->bits[3] = (dst->bits[3] | MIN_INT);
  else
    dst->bits[3] = (dst->bits[3] & MAX_INT);
}

int get_sign(s21_decimal src) {
  int sign = 0;
  if ((src.bits[3] & MIN_INT) != 0) sign = 1;
  return sign;
}

int set_scale(s21_decimal *dst, int scale) {
  if (scale < 0 || scale > 28)
    return 1;
  else {
    int is_neg = 0;
    if ((dst->bits[3] & MIN_INT) != 0) is_neg = 1;
    dst->bits[3] = (scale << 16);
    if (is_neg) set_sign(dst, 1);
  }
  return 0;
}

int get_scale(s21_decimal src) {
  int scale = 0;
  scale = (src.bits[3] & MAX_INT) >> 16;
  return scale;
}

int mantissa_to_string(s21_decimal src, char result[97]) {
  result[96] = 0;
  for (int i = 0; i < 96; i++) {
    int bit = get_bit(src, 95 - i);
    result[i] = '0' + bit;
  }
  return 0;
}

float binstring2float(char result[97]) {
  float power = 1;
  float value = 0;
  for (int i = 0; i < 96; i++) {
    if (result[95 - i] == '1') {
      value += power;
    }
    power *= 2;
  }
  return value;
}

float getMantissaF(s21_decimal src) {
  char res[97];
  mantissa_to_string(src, res);
  return binstring2float(res);
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  reset(dst);
  dst->bits[0] = src < 0 ? -src : src;
  if (src < 0) {
    set_sign(dst, 1);
    set_bit(dst, 31, 0);
  }
  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  s21_decimal dec_num = src;
  int scale = get_scale(dec_num);
  if (scale > 0) scale_decrease(&dec_num, &scale, get_scale(dec_num));
  if (get_sign(src) == 0) {
    if (dec_num.bits[1] == 0 && dec_num.bits[2] == 0 &&
        get_bit(dec_num, 31) == 0)
      *dst = dec_num.bits[0];
    else
      error = DEC_ERROR;
  } else {
    if (dec_num.bits[1] == 0 && dec_num.bits[2] == 0) {
      *dst = ~(dec_num.bits[0] - 1);
    } else
      error = DEC_ERROR;
  }
  return error;
}

int get_binexp_from_decimal(s21_decimal src) {
  int bin_exp = 95, bit = 0;
  while (!bit) {
    bit = get_bit(src, bin_exp--);
  }
  return bin_exp + 1;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  float mantissa = getMantissaF(src);
  int sign = get_sign(src);
  int scale = get_scale(src);
  float res = 0.0F;
  res += mantissa;
  res *= sign == 0 ? 1 : -1;
  res /= pow(10, scale);
  *dst = res;
  return DEC_OK;
}

int checkFloat2DecimalErrors(float src) {
  int result = DEC_OK;
  if (src > MAX_DECIMAL) {
    result = DEC_ERROR;
  }
  if (src < MIN_DECIMAL) {
    result = DEC_ERROR;
  }
  return result;
}

int getFloatStrScale(char *str) {
  int flag_decimal = 0, scale = 0, len = 0, flag_decimal_important = 0;
  int mode_no_int = 0;
  if (str[0] == '0' && str[1] == '.') {
    mode_no_int = 1;
  }
  for (int i = 0; i < (int)strlen(str) && scale < 28; i++) {
    if (mode_no_int) {
      if (str[i] == '.') {
        flag_decimal = 1;
      } else if (flag_decimal) {
        scale++;
        if (str[i] != '0') flag_decimal_important = 1;
        if (flag_decimal_important) len++;
      }
      if (len >= 7) break;
    } else {
      len++;
      if (str[i] == '.') flag_decimal = 1;
      if (len >= 7 && flag_decimal) break;
      if (flag_decimal) scale++;
      if (scale <= 0) scale--;
    }
  }
  return scale;
}

int float2binstring(float src, char result[97]) {
  memset(result, 0, 97);
  int i = 0;
  while (src > 0.0 && i < 96) {
    int bit = fmodf(src, 2.0);
    result[i] = '0' + bit;
    src /= 2;
    i++;
  }
  return i;
}
int binstrin2mantissa(s21_decimal *src, char binstring[97], int length) {
  for (int i = 0; i < length; i++) {
    int bit = binstring[i] - '0';
    set_bit(src, i, bit);
  }
  return 0;
}

float setMantissaF(s21_decimal *dst, float src) {
  char res[97];
  int length = float2binstring(src, res);
  return binstrin2mantissa(dst, res, length);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (checkFloat2DecimalErrors(src)) return DEC_ERROR;
  reset(dst);

  char str[100];
  int sign = 0, flag = 0, len = 0, divider = 10;
  double x = 0;

  if (src < 0) {
    sign = 1;
    src *= -1;
  }
  set_sign(dst, sign);

  sprintf(str, "%.35f", src);

  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '.') {
      continue;
    }
    if (!flag && str[i] != '0') flag = 1;
    double d = str[i] - '0';
    if (flag) {
      len++;
      if (len <= 7 && i <= 29)
        x = x * 10 + d;
      else if (len <= 10) {
        x = x + d / divider;
        divider *= 10;
      } else
        break;
    }
  }

  int scale = getFloatStrScale(str);

  float rounded = roundf(x);

  if (scale < 0) {
    scale += 7;
  }
  while (scale < 0) {
    rounded *= 10;
    scale++;
  }
  while (fmod(rounded, 10) < 1 && scale > 0) {
    rounded /= 10;
    scale--;
  }

  setMantissaF(dst, rounded);

  set_scale(dst, scale);

  return 0;
}
