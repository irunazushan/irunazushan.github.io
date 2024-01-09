#include <check.h>

#include "../backend/s21_smart_calc.h"

#define TOL 1e-7
#define TOL2 1e-2

START_TEST(s21_smart_calc_test_1) {
  double result = 0;
  char case_1[] = "(123+765)/0.8*4";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, 4440, TOL);
  char case_2[] = "1.00034+23*(2.672-4)/(1/2)";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, -60.08766, TOL);
  char case_3[] = "200+10.8mod4.17";
  ck_assert_int_eq(run_validation(case_3), OK);
  run_calc(case_3, &result);
  ck_assert_double_eq_tol(result, 202.46, TOL);
}
END_TEST

START_TEST(s21_smart_calc_test_2) {
  double result = 0;
  char case_1[] = "cos(23*(sqrt(57.2)))";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, -0.3966132664, TOL);
  char case_2[] = "log(9)-ln(1)";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, 0.95424250943, TOL);
  char case_3[] = "sin(cos(tan(23)))";
  ck_assert_int_eq(run_validation(case_3), OK);
  run_calc(case_3, &result);
  ck_assert_double_eq_tol(result, -0.017355013, TOL);
}
END_TEST

START_TEST(s21_smart_calc_test_3) {
  double result = 0;
  char case_1[] = "2^32.4/555478.21";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, 10202.45838911, TOL);
  char case_2[] = "3*-sqrt(5-7+9)";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, -7.937253933, TOL);
  char case_3[] = "sin(3)+26.7-ln(8)+(log(56.687)*atan(23.5)-2^4)";
  ck_assert_int_eq(run_validation(case_3), OK);
  run_calc(case_3, &result);
  ck_assert_double_eq_tol(result, 11.4414725369, TOL);
}
END_TEST

START_TEST(s21_smart_calc_test_4) {
  double result = 0;
  char case_1[] = "2**5";
  ck_assert_int_eq(run_validation(case_1), ERROR);
  char case_2[] = "2-*4";
  ck_assert_int_eq(run_validation(case_2), ERROR);
  char case_3[] = "sin(5+sqrt(6)";
  ck_assert_int_eq(run_validation(case_3), INCORRECT_BRACKETS);
  char case_4[] = "45/(7-7)";
  int errorStatus = run_calc(case_4, &result);
  ck_assert_int_eq(errorStatus, DIV_BY_ZERO);
  char *errorMessage = get_error(errorStatus);
  ck_assert_str_eq(errorMessage, "ERROR: DIV_BY_ZERO\n");
  free(errorMessage);
  char case_5[] = "cos)1(";
  errorStatus = run_validation(case_5);
  ck_assert_int_eq(errorStatus, INCORRECT_BRACKETS);
  errorMessage = get_error(errorStatus);
  ck_assert_str_eq(errorMessage, "ERROR: INCORRECT_BRACKETS\n");
  free(errorMessage);
}
END_TEST

START_TEST(s21_smart_calc_test_5) {
  double result = 0;
  char case_1[] = "log(4*0)";
  ck_assert_int_eq((run_calc(case_1, &result)), INVALID_ARG);
  char case_2[] = "ln(-23)";
  ck_assert_int_eq((run_calc(case_2, &result)), INVALID_ARG);
  char case_3[] = "sqrt(-1*34)";
  ck_assert_int_eq((run_calc(case_3, &result)), INVALID_ARG);
  char case_4[] = "acos(-1.1)";
  int errorStatus = run_calc(case_4, &result);
  ck_assert_int_eq(errorStatus, INVALID_ARG);
  char *errorMessage = get_error(errorStatus);
  ck_assert_str_eq(errorMessage, "ERROR: INVALID_ARG\n");
  char case_5[] = "asin(7.1)";
  ck_assert_int_eq((run_calc(case_5, &result)), INVALID_ARG);
  free(errorMessage);
}
END_TEST

START_TEST(s21_smart_calc_test_6) {
  double result = 0;
  char case_1[] = "-1.789023";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, -1.789023, TOL);
  char case_2[] = "5--5";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, 10, TOL);
  char case_3[] = "cos(x^2)";
  ck_assert_int_eq(run_validation(case_3), OK);
  ck_assert_int_eq((run_calc(case_3, &result)), OK);
}
END_TEST

START_TEST(s21_smart_calc_test_7) {
  double result = 0;
  char case_1[] = "atan(123)";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, 1.5626664, TOL);
  char case_2[] = "asin(0.123)";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, 0.12331227, TOL);
  char case_3[] = "acos(-0.7)";
  ck_assert_int_eq(run_validation(case_3), OK);
  run_calc(case_3, &result);
  ck_assert_double_eq_tol(result, 2.346193823, TOL);
}
END_TEST

START_TEST(s21_smart_calc_test_8) {
  double result = 0;
  char case_1[] =
      "(2+(23.54*0.1)-6)/"
      "0.01mod20+cos(34)*sin(2*(tan(73)-(acos(0.05))+asin(1)^sqrt(9)+ln(23)-"
      "log(200)))";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, 14.6068883092, TOL);
  char case_2[] = "23         +++ 43    * 0.2321  -        - 10";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, 42.9803, TOL);
  char case_3[] = "2^(-1.1^(3^(cos(0))))";
  ck_assert_int_eq(run_validation(case_3), OK);
  run_calc(case_3, &result);
  ck_assert_double_eq_tol(result, 0.3974926254, TOL);
}
END_TEST

START_TEST(s21_smart_calc_test_9) {
  double result = 0;
  char case_1[] = "(-+45)-(-+45)";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, 0, TOL);
  char case_2[] = "45 mod3.3";
  ck_assert_int_eq(run_validation(case_2), OK);
  run_calc(case_2, &result);
  ck_assert_double_eq_tol(result, 2.1, TOL);
  char case_3[] = "tan((2*((((4.4))))/9))";
  ck_assert_int_eq(run_validation(case_3), OK);
  run_calc(case_3, &result);
  ck_assert_double_eq_tol(result, 1.483819780, TOL);
}
END_TEST

START_TEST(s21_smart_calc_test_10) {
  double result = 0;
  char case_1[] = "Cos(5 +-+--+       67.342) MOd -23";
  ck_assert_int_eq(run_validation(case_1), OK);
  run_calc(case_1, &result);
  ck_assert_double_eq_tol(result, 0.882401997, TOL);
  char case_2[] = "cof(2)";
  ck_assert_int_eq(run_validation(case_2), INCORRECT_OPERATOR);
  char case_3[] = "23..312.+3";
  ck_assert_int_eq(run_validation(case_3), INCORRECT_NUMBER);
  char case_4[] = "23*8A6";
  ck_assert_int_eq(run_validation(case_4), ERROR);
  char case_5[] =
      "2*2+2*2+2+2-sqrt(9*((0-1)+1))-1+2*2+2*2+2+2-sqrt\
  (9*((0-1)+1))-1+2*2+2*2+2+2-sqrt(9*((0-1)+1))-1+2*2+2*2+2+2-sqrt(9*\
  ((0-1)+1))-1+2*2+2*2+2+2-sqrt(9*((0-1)+1))-1+2*2+2*2+2+2-sqrt(9*((0-1\
  )+1))-1+2*2+2*2+2+2-sqrt(9*((0-1)+1))-1+2*2+2*2+2+2-sqrt(9*((0-1)+1)+1204";
  ck_assert_int_eq(run_validation(case_5), OVER_SIZE);
  char case_6[] = "sqrt($)";
  ck_assert_int_eq(run_validation(case_6), INCORRECT_OPERATOR);
  ck_assert_int_eq(run_validation(NULL), ERROR);
  char case_8[] = "12.213+$$&5";
  ck_assert_int_eq(run_validation(case_8), INCORRECT_OPERATOR);
  char case_9[] = "45$87";
  ck_assert_int_eq(run_validation(case_9), INCORRECT_OPERATOR);
  char case_10[] = "+-45/";
  ck_assert_int_eq(run_validation(case_10), ERROR);
}
END_TEST

START_TEST(s21_credit_calc_test_1) {
  creditData crData = {300000, 10, 5.5, 0};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  while (months < crData.month) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
  }
  ck_assert_double_eq_tol(monthPayment, 30761.44, TOL2);
  ck_assert_double_eq_tol(overPayment, 7614.37, TOL2);
  ck_assert_double_eq_tol(totalPayment, 307614.37, TOL2);
}
END_TEST

START_TEST(s21_credit_calc_test_2) {
  creditData crData = {300000, 10, 5.5, 1};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  while (months < crData.month) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
  }
  ck_assert_double_eq_tol(monthPayment, 30137.50, TOL2);
  ck_assert_double_eq_tol(overPayment, 7562.50, TOL2);
  ck_assert_double_eq_tol(totalPayment, 307562.50, TOL2);
}
END_TEST

START_TEST(s21_credit_calc_test_3) {
  creditData crData = {55000000, 50, 2.1, 0};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  while (months < crData.month) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
  }
  ck_assert_double_eq_tol(monthPayment, 1149788.34, TOL2);
  ck_assert_double_eq_tol(overPayment, 2489416.99, TOL2);
  ck_assert_double_eq_tol(totalPayment, 57489416.99, TOL2);
}
END_TEST

START_TEST(s21_credit_calc_test_4) {
  creditData crData = {55000000, 50, 2.1, 1};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  while (months < crData.month) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
    if (months == 35) {
      ck_assert_double_eq_tol(monthPayment, 1130800.00, TOL2);
    }
  }
  ck_assert_double_eq_tol(monthPayment, 1101925.00, TOL2);
  ck_assert_double_eq_tol(overPayment, 2454375.00, TOL2);
  ck_assert_double_eq_tol(totalPayment, 57454375.00, TOL2);
}
END_TEST

START_TEST(s21_credit_calc_test_5) {
  creditData crData = {6000000, 18, 14.7, 0};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  while (months < crData.month) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
  }
  ck_assert_double_eq_tol(monthPayment, 373462.14, TOL2);
  ck_assert_double_eq_tol(overPayment, 722318.53, TOL2);
  ck_assert_double_eq_tol(totalPayment, 6722318.53, TOL2);
}
END_TEST

START_TEST(s21_credit_calc_test_6) {
  creditData crData = {6000000, 18, 14.7, 1};
  double monthPayment = 0.0, overPayment = 0.0, totalPayment = 0.0;
  int months = 0;
  while (months < crData.month) {
    credit_calculator(crData, &monthPayment, &overPayment, &totalPayment,
                      &months);
    if (months == 12) {
      ck_assert_double_eq_tol(monthPayment, 361916.67, TOL2);
    }
  }
  ck_assert_double_eq_tol(monthPayment, 337416.67, TOL2);
  ck_assert_double_eq_tol(overPayment, 698250.00, TOL2);
  ck_assert_double_eq_tol(totalPayment, 6698250.00, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_1) {
  depositData depData = {1000000, 65, 13, 13, 16, 1};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.balance, 1994797.86, TOL2);
  ck_assert_double_eq_tol(report.tax, 0.00, TOL2);
  ck_assert_double_eq_tol(report.accruedCash, 104626.76, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_2) {
  depositData depData = {1000000, 65, 13, 13, 16, 0};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.balance, 1704166.67, TOL2);
  ck_assert_double_eq_tol(report.cashFlow, 54166.67, TOL2);
  ck_assert_double_eq_tol(report.accruedCash, 54166.67, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_3) {
  depositData depData = {6000000, 24, 11.7, 13, 16, 0};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.accruedCash, 702000.00, TOL2);
  ck_assert_double_eq_tol(report.tax, 70460.00, TOL2);
  ck_assert_double_eq_tol(report.balance, 7263080.00, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_4) {
  depositData depData = {6000000, 24, 11.7, 13, 16, 1};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.accruedCash, 823058.19, TOL2);
  ck_assert_double_eq_tol(report.tax, 86197.56, TOL2);
  ck_assert_double_eq_tol(report.balance, 7402239.68, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_5) {
  depositData depData = {4500000, 120, 13.1, 15, 20, 0};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.balance, 9810750.00, TOL2);
  ck_assert_double_eq_tol(report.cashFlow, 531075.00, TOL2);
  ck_assert_double_eq_tol(report.accruedCash, 589500.00, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_6) {
  depositData depData = {4500000, 120, 13.1, 15, 20, 1};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.balance, 14285889.73, TOL2);
  ck_assert_double_eq_tol(report.tax, 236099.37, TOL2);
  ck_assert_double_eq_tol(report.accruedCash, 1773995.81, TOL2);
}
END_TEST

START_TEST(s21_deposit_calc_test_7) {
  depositData depData = {20000000, 120, 13.1, 15, 20, 1};
  Report report = {0, 0, 0, 0, depData.depositSum};
  for (; report.period < depData.fullPeriod;) {
    deposit_calculator(depData, &report);
  }
  ck_assert_double_eq_tol(report.balance, 61102382.37, TOL2);
  ck_assert_double_eq_tol(report.tax, 1261107.49, TOL2);
  ck_assert_double_eq_tol(report.accruedCash, 7618279.34, TOL2);
}
END_TEST

/* SUIT CREATING */

Suite *s21_smart_calc_suite(void) {
  Suite *suite = suite_create("s21_smart_calc");
  TCase *tc_core = tcase_create("core_of_smart_calc");
  tcase_add_test(tc_core, s21_smart_calc_test_1);
  tcase_add_test(tc_core, s21_smart_calc_test_2);
  tcase_add_test(tc_core, s21_smart_calc_test_3);
  tcase_add_test(tc_core, s21_smart_calc_test_4);
  tcase_add_test(tc_core, s21_smart_calc_test_5);
  tcase_add_test(tc_core, s21_smart_calc_test_6);
  tcase_add_test(tc_core, s21_smart_calc_test_7);
  tcase_add_test(tc_core, s21_smart_calc_test_8);
  tcase_add_test(tc_core, s21_smart_calc_test_9);
  tcase_add_test(tc_core, s21_smart_calc_test_10);
  suite_add_tcase(suite, tc_core);
  return suite;
}

Suite *s21_credit_calc_suite(void) {
  Suite *suite = suite_create("s21_credit_calc");
  TCase *tc_core = tcase_create("core_of_credit_calc");
  tcase_add_test(tc_core, s21_credit_calc_test_1);
  tcase_add_test(tc_core, s21_credit_calc_test_2);
  tcase_add_test(tc_core, s21_credit_calc_test_3);
  tcase_add_test(tc_core, s21_credit_calc_test_4);
  tcase_add_test(tc_core, s21_credit_calc_test_5);
  tcase_add_test(tc_core, s21_credit_calc_test_6);
  suite_add_tcase(suite, tc_core);
  return suite;
}
Suite *s21_deposit_calc_suite(void) {
  Suite *suite = suite_create("s21_deposit_calc");
  TCase *tc_core = tcase_create("core_of_deposit_calc");
  tcase_add_test(tc_core, s21_deposit_calc_test_1);
  tcase_add_test(tc_core, s21_deposit_calc_test_2);
  tcase_add_test(tc_core, s21_deposit_calc_test_3);
  tcase_add_test(tc_core, s21_deposit_calc_test_4);
  tcase_add_test(tc_core, s21_deposit_calc_test_5);
  tcase_add_test(tc_core, s21_deposit_calc_test_6);
  tcase_add_test(tc_core, s21_deposit_calc_test_7);
  suite_add_tcase(suite, tc_core);
  return suite;
}

/* EXECUTION */

void s21_suit_executer(Suite *suite, int *fail_counter, char *log_name) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_set_log(suite_runner, log_name);
  srunner_run_all(suite_runner, CK_NORMAL);
  *fail_counter += srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main() {
  int fail_counter = 0;

  s21_suit_executer(s21_smart_calc_suite(), &fail_counter,
                    "test_log/s21_smart_calc.log");
  s21_suit_executer(s21_credit_calc_suite(), &fail_counter,
                    "test_log/s21_credit_calc.log");
  s21_suit_executer(s21_deposit_calc_suite(), &fail_counter,
                    "test_log/s21_deposit_calc.log");

  return fail_counter == 0 ? 0 : 1;
}
