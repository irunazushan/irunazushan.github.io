#include <check.h>

#include "s21_decimal.h"

int float_cmp(float fn, float f) {
  return (fn - f < 0.000000000000001) || (f - fn < 0.000000000000001);
}

// compare funcs

START_TEST(is_less) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(dec1, dec2));
  s21_decimal dec3 = {{15, 0, 0, 0}};
  s21_decimal dec4 = {{15, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(dec3, dec4));
  s21_decimal dec5 = {{15, 1, 0, 0}};
  s21_decimal dec6 = {{15, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less(dec6, dec5));
  s21_decimal dec7 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  s21_decimal dec8 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  ck_assert_int_eq(0, s21_is_less(dec7, dec8));
  s21_decimal dec9 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec10 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(dec9, dec10));
}
END_TEST

START_TEST(is_less_or_equal) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(dec1, dec2));
  s21_decimal dec3 = {{15, 0, 0, 0}};
  s21_decimal dec4 = {{15, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(dec3, dec4));
  s21_decimal dec5 = {{15, 1, 0, 0}};
  s21_decimal dec6 = {{15, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(dec6, dec5));
  s21_decimal dec7 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  s21_decimal dec8 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(dec7, dec8));
  s21_decimal dec9 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec10 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  ck_assert_int_eq(1, s21_is_less_or_equal(dec9, dec10));
}
END_TEST

START_TEST(is_greater_or_equal) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec1, dec2));
  s21_decimal dec3 = {{15, 0, 0, 0}};
  s21_decimal dec4 = {{15, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec3, dec4));
  s21_decimal dec5 = {{15, 1, 0, 0}};
  s21_decimal dec6 = {{15, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_greater_or_equal(dec6, dec5));
  s21_decimal dec7 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  s21_decimal dec8 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec7, dec8));
  s21_decimal dec9 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec10 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec9, dec10));
}
END_TEST

START_TEST(is_not_equal) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(dec1, dec2));
  s21_decimal dec3 = {{15, 0, 0, 0}};
  s21_decimal dec4 = {{15, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(dec3, dec4));
  s21_decimal dec5 = {{15, 1, 0, 0}};
  s21_decimal dec6 = {{15, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_not_equal(dec6, dec5));
  s21_decimal dec7 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  s21_decimal dec8 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  ck_assert_int_eq(0, s21_is_not_equal(dec7, dec8));

  // convertors
}
END_TEST

START_TEST(from_int_to_dec) {
  int a1 = MAX_INT;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a1, &dec1);
  ck_assert_int_eq(MAX_INT, dec1.bits[0]);
  int a2 = 0;
  s21_decimal dec2 = {{123, 0, 0, 0}};
  s21_from_decimal_to_int(dec2, &a2);
  ck_assert_int_eq(123, a2);
  int a22 = 0;
  int a12 = -123;
  s21_decimal dec22 = {{
      0,
      0,
      0,
      0,
  }};
  s21_from_int_to_decimal(a12, &dec22);
  s21_from_decimal_to_int(dec22, &a22);
  ck_assert_int_eq(-123, a22);

  int a3 = 12345;
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a3, &dec3);
  ck_assert_int_eq(12345, dec3.bits[0]);
  int a4 = -2345;
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(a4, &dec4);
  ck_assert_int_eq(1, get_sign(dec4));
  ck_assert_int_eq(2345, dec4.bits[0]);
}
END_TEST

START_TEST(from_float_to_dec) {
  float f1 = 0.00000000000000012;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(f1, &dec1);

  float f2 = 0.0000000000000001;
  s21_decimal dec2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(f2, &dec2);

  float f3 = -0.00000000000000012;
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(f3, &dec3);
  ck_assert_int_eq(1, get_sign(dec3));

  float f4 = -97849748.798745;
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(f4, &dec4);
  ck_assert_int_eq(1, get_sign(dec4));

  s21_decimal dec12 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec13 = {{9, 0, 0, 0}};
  set_scale(&dec12, 21);
  set_scale(&dec13, 21);
  s21_decimal res1213 = {{0, 0, 0, 0}};
  s21_add(dec1, dec2, &res1213);
}
END_TEST

START_TEST(from_dec_to_int) {
  int neg = 2147483648;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  int a1 = 1;
  s21_from_decimal_to_int(dec1, &a1);
  ck_assert_int_eq(0, a1);
  s21_decimal dec2 = {{MAX_INT, 0, 0, 0}};
  int a2 = 1;
  s21_from_decimal_to_int(dec2, &a2);
  ck_assert_int_eq(MAX_INT, a2);
  s21_decimal dec3 = {{5, 0, 0, neg}};
  int a3 = 1;
  s21_from_decimal_to_int(dec3, &a3);
  ck_assert_int_eq(-5, a3);
  int a4 = 1;
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(2.123, &dec4);
  s21_from_decimal_to_int(dec4, &a4);

  ck_assert_int_eq(2, a4);

  int a5 = 1;
  s21_decimal dec5 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(999988.05, &dec5);
  s21_from_decimal_to_int(dec5, &a5);
  ck_assert_int_eq(999988, a5);
}
END_TEST

START_TEST(from_dec_to_float) {
  float f = 0;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  float f1 = 0.123;
  s21_from_float_to_decimal(f1, &dec1);
  s21_from_decimal_to_float(dec1, &f);
  ck_assert_float_eq(1, float_cmp(f1, f));

  s21_decimal dec2 = {{0, 0, 0, 0}};
  float f2 = -0.123002;
  s21_from_float_to_decimal(f2, &dec2);
  s21_from_decimal_to_float(dec2, &f);
  ck_assert_float_eq(1, float_cmp(f2, f));

  s21_decimal dec3 = {{0, 0, 0, 0}};
  float f3 = -0.000000021;
  s21_from_float_to_decimal(f3, &dec3);
  s21_from_decimal_to_float(dec3, &f);
  ck_assert_float_eq(1, float_cmp(f3, f));

  s21_decimal dec4 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  float f4 = 0;

  s21_from_decimal_to_float(dec4, &f4);

  // arithmetics
}
END_TEST

START_TEST(subtract) {
  s21_decimal dec1 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec2 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal res12 = {{0, 0, 0, 0}};
  s21_sub(dec1, dec2, &res12);
  ck_assert_int_eq(0, res12.bits[0]);
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_decimal res34 = {{1, 0, 0, 0}};
  s21_sub(dec3, dec4, &res34);
  ck_assert_int_eq(0, res34.bits[0]);
  s21_decimal dec5 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  s21_decimal dec6 = {{MAX_INT, MAX_INT, MAX_INT, 0}};
  s21_decimal res56 = {{1, 0, 0, 0}};
  s21_sub(dec6, dec5, &res56);
  ck_assert_int_eq(0, res56.bits[0]);

  s21_decimal dec8 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec9;
  s21_decimal res88;

  float f = 0.6;
  s21_from_float_to_decimal(f, &dec9);
  s21_sub(dec8, dec9, &res88);
}
END_TEST

START_TEST(add) {
  s21_decimal dec1 = {{3, 0, 0, 0}};
  s21_decimal dec2 = {{1, 0, 0, 0}};
  s21_decimal res12 = {{0, 0, 0, 0}};
  s21_add(dec1, dec2, &res12);
  ck_assert_int_eq(4, res12.bits[0]);

  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_decimal res34 = {{0, 0, 0, 0}};

  float f3 = 0.000003;
  float f4 = -0.00000000234;
  float f = 0;
  s21_from_float_to_decimal(f3, &dec3);
  s21_from_float_to_decimal(f4, &dec4);
  s21_add(dec3, dec4, &res34);
  s21_from_decimal_to_float(res34, &f);
  ck_assert_float_eq(1, float_cmp(f3 + f3, f));

  s21_decimal dec8 = {
      {(MAX_INT << 1), (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};
  s21_decimal dec9 = {{6, 0, 0, 0}};
  set_scale(&dec9, 1);
  s21_decimal res88;
  s21_add(dec8, dec9, &res88);

  s21_decimal exp3 = {
      {(MAX_INT << 1) + 1, (MAX_INT << 1) + 1, (MAX_INT << 1) + 1, 0}};

  ck_assert_int_eq(1, s21_is_equal(exp3, res88));

  s21_decimal dec_numb1 = {{0, 0, 0, 0}};
  s21_decimal dec_numb2 = {{0, 0, 0, 0}};
  s21_decimal exp44 = {
      {0b10011001100110011001100110011001, 0b10011001100110011001100110011001,
       0b00011001100110011001100110011001, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};

  dec_numb1.bits[2] = (MAX_INT << 1) + 1;
  dec_numb1.bits[1] = (MAX_INT << 1) + 1;
  dec_numb1.bits[0] = (MAX_INT << 1);
  set_sign(&dec_numb1, 1);
  set_scale(&dec_numb1, 1);

  s21_from_int_to_decimal(0, &dec_numb2);
  set_sign(&dec_numb2, 1);
  set_scale(&dec_numb2, 1);

  s21_add(dec_numb1, dec_numb2, &result);
  ck_assert_int_eq(1, s21_is_equal(result, exp44));
}
END_TEST

START_TEST(mul) {
  int neg = 2147483648;
  s21_decimal dec1 = {{2, 0, 0, neg}};
  s21_decimal dec2 = {{4, 0, 0, 0}};
  s21_decimal res12 = {{0, 0, 0, 0}};
  s21_mul(dec1, dec2, &res12);
  ck_assert_int_eq(1, get_sign(res12));

  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_decimal res34 = {{0, 0, 0, 0}};
  float f3 = 0.012;
  float f4 = 0.0099;
  float fres = f3 * f4;
  float fd = 0;
  s21_from_float_to_decimal(f3, &dec3);
  s21_from_float_to_decimal(f4, &dec4);
  s21_mul(dec3, dec4, &res34);
  s21_from_decimal_to_float(res34, &fd);
  ck_assert_int_eq(1, float_cmp(fd, fres));

  s21_decimal dec5 = {{0, 0, 0, 0}};
  s21_decimal dec6 = {{0, 0, 0, 0}};
  s21_decimal res56 = {{0, 0, 0, 0}};
  float f5 = -0.0000012;
  float f6 = 0.00099;
  fres = f5 * f6;
  fd = 0;
  s21_from_float_to_decimal(f5, &dec5);
  s21_from_float_to_decimal(f6, &dec6);
  s21_mul(dec5, dec6, &res56);
  s21_from_decimal_to_float(res56, &fd);
  ck_assert_int_eq(1, float_cmp(fd, fres));
}
END_TEST

START_TEST(negate) {
  int neg = 2147483648;
  s21_decimal dec1 = {{23, 456, 234, 0}};
  s21_decimal res1 = {{0, 0, 0, 0}};
  int sign_dec1 = get_sign(dec1);
  s21_negate(dec1, &res1);
  int sign_res1 = get_sign(res1);
  ck_assert_int_ne(sign_dec1, sign_res1);

  s21_decimal dec2 = {{23, 456, 234, neg}};
  s21_decimal res2 = {{0, 0, 0, 0}};
  int sign_dec2 = get_sign(dec2);
  s21_negate(dec2, &res2);
  int sign_res2 = get_sign(res2);
  ck_assert_int_ne(sign_dec2, sign_res2);
}
END_TEST

START_TEST(trunc_dec) {
  float f = -12.0042;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dect = {{0, 0, 0, 0}};

  s21_decimal res1 = {{0, 0, 0, 0}};
  float tf = -12;
  s21_from_float_to_decimal(f, &dec1);
  s21_from_float_to_decimal(tf, &dect);
  s21_truncate(dec1, &res1);

  ck_assert_int_eq(1, s21_is_equal(res1, dect));

  f = 12.0042;
  s21_decimal dec2 = {{0, 0, 0, 0}};
  s21_decimal dect2 = {{0, 0, 0, 0}};

  s21_decimal res2 = {{0, 0, 0, 0}};
  tf = 12;
  s21_from_float_to_decimal(f, &dec2);
  s21_from_float_to_decimal(tf, &dect2);
  s21_truncate(dec2, &res2);

  ck_assert_int_eq(1, s21_is_equal(res2, dect2));
}
END_TEST

START_TEST(floor_dec) {
  float f = -12.0042;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dect = {{0, 0, 0, 0}};

  s21_decimal res1 = {{0, 0, 0, 0}};
  float tf = -13;
  s21_from_float_to_decimal(f, &dec1);
  s21_from_float_to_decimal(tf, &dect);
  s21_floor(dec1, &res1);

  f = 12.0042;
  s21_decimal dec2 = {{0, 0, 0, 0}};
  s21_decimal decf2 = {{0, 0, 0, 0}};

  s21_decimal res2 = {{0, 0, 0, 0}};
  tf = 12;
  s21_from_float_to_decimal(f, &dec2);
  s21_from_float_to_decimal(tf, &decf2);
  s21_truncate(dec2, &res2);

  ck_assert_int_eq(1, s21_is_equal(res2, decf2));
}
END_TEST

START_TEST(round_dec) {
  float f = -12.0042;
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dect = {{0, 0, 0, 0}};

  s21_decimal res1 = {{0, 0, 0, 0}};
  float tf = -12;
  s21_from_float_to_decimal(f, &dec1);
  s21_from_float_to_decimal(tf, &dect);
  s21_round(dec1, &res1);

  ck_assert_int_eq(1, s21_is_equal(res1, dect));

  f = 12.0042;
  s21_decimal dec2 = {{0, 0, 0, 0}};
  s21_decimal decf2 = {{0, 0, 0, 0}};

  s21_decimal res2 = {{0, 0, 0, 0}};
  tf = 12;
  s21_from_float_to_decimal(f, &dec2);
  s21_from_float_to_decimal(tf, &decf2);
  s21_round(dec2, &res2);

  ck_assert_int_eq(1, s21_is_equal(res2, decf2));

  f = 12.545;
  s21_decimal dec3 = {{0, 0, 0, 0}};
  s21_decimal decf3 = {{0, 0, 0, 0}};

  s21_decimal res3 = {{0, 0, 0, 0}};
  tf = 13;
  s21_from_float_to_decimal(f, &dec3);
  s21_from_float_to_decimal(tf, &decf3);
  s21_round(dec3, &res3);

  ck_assert_int_eq(1, s21_is_equal(res3, decf3));

  f = -12.545;
  s21_decimal dec4 = {{0, 0, 0, 0}};
  s21_decimal decf4 = {{0, 0, 0, 0}};

  s21_decimal res4 = {{0, 0, 0, 0}};
  tf = -13;
  s21_from_float_to_decimal(f, &dec4);
  s21_from_float_to_decimal(tf, &decf4);
  s21_round(dec4, &res4);

  ck_assert_int_eq(1, s21_is_equal(res4, decf4));
}
END_TEST

// 79228162514264337593543950335 * 1.1 = INF
START_TEST(test_96_bit_3) {
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal input2 = {{11, 0, 0, 0}};
  set_scale(&input2, 1);
  s21_decimal result;
  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, DEC_HUGE);
}

START_TEST(test_96_bit_4) {
  int neg = 2147483648;
  s21_decimal input1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, neg}};
  s21_decimal input2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal result;
  int status = s21_mul(input1, input2, &result);

  ck_assert_int_eq(status, DEC_SMALL);
}

START_TEST(div) {
  s21_decimal inp1 = {{225, 0, 0, 0}};
  s21_decimal inp2 = {{17, 0, 0, 0}};
  s21_decimal exp = {{15, 0, 0, 0}};
  s21_decimal res1;
  s21_div(inp1, inp2, &res1);
  ck_assert_int_eq(0, s21_is_equal(exp, res1));

  s21_decimal inp3 = {{2, 0, 0, 0}};
  s21_decimal inp4 = {{3, 0, 0, 0}};
  s21_decimal exp2 = {{0b10011010101010101010101010101011,
                       0b1101010100010110000000000101000,
                       0b10001001110111010000101000, 0}};
  set_scale(&exp2, 27);

  s21_decimal res2;
  s21_div(inp3, inp4, &res2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, is_less);
  tcase_add_test(tc1_1, is_less_or_equal);
  tcase_add_test(tc1_1, is_greater_or_equal);
  tcase_add_test(tc1_1, is_not_equal);
  tcase_add_test(tc1_1, from_int_to_dec);
  tcase_add_test(tc1_1, from_float_to_dec);
  tcase_add_test(tc1_1, from_dec_to_int);
  tcase_add_test(tc1_1, from_dec_to_float);
  tcase_add_test(tc1_1, subtract);
  tcase_add_test(tc1_1, add);
  tcase_add_test(tc1_1, mul);
  tcase_add_test(tc1_1, negate);
  tcase_add_test(tc1_1, trunc_dec);
  tcase_add_test(tc1_1, floor_dec);
  tcase_add_test(tc1_1, round_dec);
  tcase_add_test(tc1_1, div);
  tcase_add_test(tc1_1, test_96_bit_3);
  tcase_add_test(tc1_1, test_96_bit_4);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
