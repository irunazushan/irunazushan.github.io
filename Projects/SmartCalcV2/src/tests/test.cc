#include <gtest/gtest.h>

#include "../model/calculator_model.h"
#include "../model/credit_model.h"
#include "../model/deposit_model.h"

#define TOL 1e-7
#define TOL2 1e-2

enum ErrorStates {
  kOk,
  kError,
  kOverSize,
  kIncorrectOperator,
  kIncorrectBrackets,
  kIncorrectNumber,
  kDivByZero,
  kInvalidArg,
  kEmptyBrackets
};

TEST(CalculatorModel, test_1) {
  s21::CalculatorModel user;
  std::string case_1 = "(2E+3-7e-1+45)-(5 /45*7^5+sqrt(5))";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), 174.61948757, TOL);
  std::string case_2 = "1.00034+23*(2.672-4)/(1/2)";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), -60.08766, TOL);
  std::string case_3 = "200+10.8mod4.17";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
  EXPECT_NEAR(user.getResult(), 202.46, TOL);
}

TEST(CalculatorModel, test_2) {
  s21::CalculatorModel user;
  std::string case_1 = "cos(23*(sqrt(57.2)))";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), -0.3966132664, TOL);
  std::string case_2 = "log(9)-ln(1)";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), 0.95424250943, TOL);
  std::string case_3 = "sin(cos(tan(23)))";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
  EXPECT_NEAR(user.getResult(), -0.017355013, TOL);
}

TEST(CalculatorModel, test_3) {
  s21::CalculatorModel user;
  std::string case_1 = "2^32.4/555478.21";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), 10202.45838911, TOL);
  std::string case_2 = "3*-sqrt(5-7+9)";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), -7.937253933, TOL);
  std::string case_3 = "sin(3)+26.7-ln(8)+(log(56.687)*atan(23.5)-2^4)";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
  EXPECT_NEAR(user.getResult(), 11.4414725369, TOL);
}

TEST(CalculatorModel, test_4) {
  s21::CalculatorModel user;
  std::string case_1 = "2**5";
  EXPECT_EQ(user.runCalculator(case_1, 0), kError);
  std::string case_2 = "2-*4";
  EXPECT_EQ(user.runCalculator(case_2, 0), kError);
  std::string case_3 = "sin(5+sqrt(6)";
  EXPECT_EQ(user.runCalculator(case_3, 0), kIncorrectBrackets);
  std::string case_4 = "45/(7-7)";
  int errorStatus = user.runCalculator(case_4, 0);
  EXPECT_EQ(errorStatus, kDivByZero);
  std::string errorMessage = user.getErrorMessage();
  EXPECT_EQ(errorMessage, "ERROR: Div by Zero\n");
  std::string case_5 = "cos)1(";
  errorStatus = user.runCalculator(case_5, 0);
  EXPECT_EQ(errorStatus, kIncorrectBrackets);
  errorMessage = user.getErrorMessage();
  EXPECT_EQ(errorMessage, "ERROR: Incorrect Brackets\n");
  std::string case_6 = "cos+8";
  errorStatus = user.runCalculator(case_6, 0);
  EXPECT_EQ(errorStatus, kIncorrectBrackets);
  errorMessage = user.getErrorMessage();
  EXPECT_EQ(errorMessage, "ERROR: Incorrect Brackets\n");
  std::string case_7 = "cos()+2";
  errorStatus = user.runCalculator(case_7, 0);
  EXPECT_EQ(errorStatus, kEmptyBrackets);
  errorMessage = user.getErrorMessage();
  EXPECT_EQ(errorMessage, "ERROR: Empty Brackets\n");
}

TEST(CalculatorModel, test_5) {
  s21::CalculatorModel user;
  std::string case_1 = "log(4*0)";
  EXPECT_EQ(user.runCalculator(case_1, 0), kInvalidArg);
  std::string case_2 = "ln(-23)";
  EXPECT_EQ(user.runCalculator(case_2, 0), kInvalidArg);
  std::string case_3 = "sqrt(-1*34)";
  EXPECT_EQ(user.runCalculator(case_3, 0), kInvalidArg);
  std::string case_4 = "acos(-1.1)";
  int errorStatus = user.runCalculator(case_4, 0);
  EXPECT_EQ(errorStatus, kInvalidArg);
  std::string errorMessage = user.getErrorMessage();
  EXPECT_EQ(errorMessage, "ERROR: Invalid Arg\n");
  std::string case_5 = "asin(7.1)";
  EXPECT_EQ(user.runCalculator(case_5, 0), kInvalidArg);
  std::string case_6 = "asin()";
  EXPECT_EQ(user.runCalculator(case_6, 0), kEmptyBrackets);
  std::string case_7 = "cos(*8)";
  EXPECT_EQ(user.runCalculator(case_7, 0), kError);
  std::string case_8 = "sin(mod9)";
  EXPECT_EQ(user.runCalculator(case_8, 0), kError);
}

TEST(CalculatorModel, test_6) {
  s21::CalculatorModel user;
  std::string case_1 = "-1.789023";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), -1.789023, TOL);
  std::string case_2 = "5--5";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), 10, TOL);
  std::string case_3 = "cos(x^2)";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
}

TEST(CalculatorModel, test_7) {
  s21::CalculatorModel user;
  std::string case_1 = "atan(123)";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), 1.5626664, TOL);
  std::string case_2 = "asin(0.123)";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), 0.12331227, TOL);
  std::string case_3 = "acos(-0.7)";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
  EXPECT_NEAR(user.getResult(), 2.346193823, TOL);
}

TEST(CalculatorModel, test_8) {
  s21::CalculatorModel user;
  std::string case_1 =
      "(2+(23.54*0.1)-6)/"
      "0.01mod20+cos(34)*sin(2*(tan(73)-(acos(0.05))+asin(1)^sqrt(9)+ln(23)-"
      "log(200)))";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), 14.6068883092, TOL);
  std::string case_2 = "23         +++ 43    * 0.2321  -        - 10";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), 42.9803, TOL);
  std::string case_3 = "2^(-1.1^(3^(cos(0))))";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
  EXPECT_NEAR(user.getResult(), 0.3974926254, TOL);
}

TEST(CalculatorModel, test_9) {
  s21::CalculatorModel user;
  std::string case_1 = "(-+45)-(-+45)";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), 0, TOL);
  std::string case_2 = "45 mod3.3";
  EXPECT_EQ(user.runCalculator(case_2, 0), kOk);
  EXPECT_NEAR(user.getResult(), 2.1, TOL);
  std::string case_3 = "tan((2*((((4.4))))/9))";
  EXPECT_EQ(user.runCalculator(case_3, 0), kOk);
  EXPECT_NEAR(user.getResult(), 1.483819780, TOL);
}

TEST(CalculatorModel, test_10) {
  s21::CalculatorModel user;
  std::string case_1 = "Cos(5 +-+--+       67.342) MOd -23";
  EXPECT_EQ(user.runCalculator(case_1, 0), kOk);
  EXPECT_NEAR(user.getResult(), 0.882401997, TOL);
  std::string case_2 = "cof(2)";
  EXPECT_EQ(user.runCalculator(case_2, 0), kIncorrectOperator);
  std::string case_3 = "23..312.+3";
  EXPECT_EQ(user.runCalculator(case_3, 0), kIncorrectNumber);
  std::string case_4 = "23*8A6";
  EXPECT_EQ(user.runCalculator(case_4, 0), kError);
  std::string case_5 =
      "2*2+2*2+2+2-sqrt(9*((0-1)+1))-1+2*2+2*2+2+2-sqrt(9)+acos(0.2)+2*2+2*2+2+"
      "2-sqrt(9*((0-1)+1))-1+2*2+2*2+2+2-sqrt(9)+acos(0.2)+2*2+2*2+2+2-sqrt(9*("
      "(0-1)+1))-1+2*2+2*2+2+2-sqrt(9)+acos(0.2)+2*2+2*2+2+2-sqrt(9*((0-1)+1))-"
      "1+2*2+2*2+2+2-sqrt(9)+acos(0.2)+2*2+3454";
  EXPECT_EQ(user.runCalculator(case_5, 0), kOverSize);
  std::string case_6 = "sqrt($)";
  EXPECT_EQ(user.runCalculator(case_6, 0), kIncorrectOperator);
  std::string case_8 = "12.213+$$&5";
  EXPECT_EQ(user.runCalculator(case_8, 0), kIncorrectOperator);
  std::string case_9 = "45$87";
  EXPECT_EQ(user.runCalculator(case_9, 0), kIncorrectOperator);
  std::string case_10 = "+-45/";
  EXPECT_EQ(user.runCalculator(case_10, 0), kError);
}

TEST(CreditCalculatorModel, test_1) {
  s21::CreditCalculatorModel user({300000, 10, 5.5, 0});
  while (user.isEndOfMonths()) {
    user.creditCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 30761.44, TOL2);
  EXPECT_NEAR(report[1], 7614.37, TOL2);
  EXPECT_NEAR(report[2], 307614.37, TOL2);
}

TEST(CreditCalculatorModel, test_2) {
  s21::CreditCalculatorModel user({300000, 10, 5.5, 1});
  while (user.isEndOfMonths()) {
    user.creditCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 30137.50, TOL2);
  EXPECT_NEAR(report[1], 7562.50, TOL2);
  EXPECT_NEAR(report[2], 307562.50, TOL2);
}

TEST(CreditCalculatorModel, test_3) {
  s21::CreditCalculatorModel user({55000000, 50, 2.1, 0});
  while (user.isEndOfMonths()) {
    user.creditCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 1149788.34, TOL2);
  EXPECT_NEAR(report[1], 2489416.99, TOL2);
  EXPECT_NEAR(report[2], 57489416.99, TOL2);
}

TEST(CreditCalculatorModel, test_4) {
  s21::CreditCalculatorModel user({55000000, 50, 2.1, 1});
  while (user.isEndOfMonths()) {
    user.creditCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 1101925.00, TOL2);
  EXPECT_NEAR(report[1], 2454375.00, TOL2);
  EXPECT_NEAR(report[2], 57454375.00, TOL2);
}

TEST(CreditCalculatorModel, test_5) {
  s21::CreditCalculatorModel user({6000000, 18, 14.7, 0});
  while (user.isEndOfMonths()) {
    user.creditCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 373462.14, TOL2);
  EXPECT_NEAR(report[1], 722318.53, TOL2);
  EXPECT_NEAR(report[2], 6722318.53, TOL2);
}

TEST(CreditCalculatorModel, test_6) {
  s21::CreditCalculatorModel user({6000000, 18, 14.7, 1});
  while (user.isEndOfMonths()) {
    user.creditCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 337416.67, TOL2);
  EXPECT_NEAR(report[1], 698250.00, TOL2);
  EXPECT_NEAR(report[2], 6698250.00, TOL2);
}

TEST(DepositCalculatorModel, test_1) {
  s21::DepositCalculatorModel user({1000000, 65, 13, 13, 16, 1});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 1994797.86, TOL2);
  EXPECT_NEAR(report[1], 0.00, TOL2);
  EXPECT_NEAR(report[3], 104626.76, TOL2);
}

TEST(DepositCalculatorModel, test_2) {
  s21::DepositCalculatorModel user({1000000, 65, 13, 13, 16, 0});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 1704166.67, TOL2);
  EXPECT_NEAR(report[2], 54166.67, TOL2);
  EXPECT_NEAR(report[3], 54166.67, TOL2);
}

TEST(DepositCalculatorModel, test_3) {
  s21::DepositCalculatorModel user({6000000, 24, 11.7, 13, 16, 0});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[3], 702000.00, TOL2);
  EXPECT_NEAR(report[1], 70460.00, TOL2);
  EXPECT_NEAR(report[0], 7263080.00, TOL2);
}

TEST(DepositCalculatorModel, test_4) {
  s21::DepositCalculatorModel user({6000000, 24, 11.7, 13, 16, 1});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[3], 823058.19, TOL2);
  EXPECT_NEAR(report[1], 86197.56, TOL2);
  EXPECT_NEAR(report[0], 7402239.68, TOL2);
}

TEST(DepositCalculatorModel, test_5) {
  s21::DepositCalculatorModel user({4500000, 120, 13.1, 15, 20, 0});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 9810750.00, TOL2);
  EXPECT_NEAR(report[2], 531075.00, TOL2);
  EXPECT_NEAR(report[3], 589500.00, TOL2);
}

TEST(DepositCalculatorModel, test_6) {
  s21::DepositCalculatorModel user({4500000, 120, 13.1, 15, 20, 1});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 14285889.73, TOL2);
  EXPECT_NEAR(report[1], 236099.37, TOL2);
  EXPECT_NEAR(report[3], 1773995.81, TOL2);
}

TEST(DepositCalculatorModel, test_7) {
  s21::DepositCalculatorModel user({20000000, 120, 13.1, 15, 20, 1});
  for (; user.isEndOfPeriod();) {
    user.depositCalculator();
  }
  auto report = user.getReport();
  EXPECT_NEAR(report[0], 61102382.37, TOL2);
  EXPECT_NEAR(report[1], 1261107.49, TOL2);
  EXPECT_NEAR(report[3], 7618279.34, TOL2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
