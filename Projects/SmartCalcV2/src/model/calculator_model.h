#ifndef CALCULATOR_MODEL_H
#define CALCULATOR_MODEL_H

#include <cctype>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#define MAX_SIZE 255

namespace s21 {

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

class CalculatorModel {
 public:
  enum Tokens {
    kNumber,
    kX,
    kPlus,
    kMinus,
    kMult,
    kDiv,
    kMod,
    kPow,
    kSqrt,
    kSin,
    kCos,
    kTan,
    kAcos,
    kAsin,
    kAtan,
    kLn,
    kLog,
    kUnMinus,
    kUnPlus,
    kOpenBracket,
    kCloseBracket,
    kStopFlag
  };

  CalculatorModel() = default;
  ~CalculatorModel() = default;
  void runValidation(std::string& inputStr);
  void expressionToStack();
  void convertStackToRpnStack();
  void calculation(double x);
  std::string getErrorMessage();
  double getResult();
  int getError();
  void clean();
  int runCalculator(std::string& expression, double x);

 private:
  struct DataSet {
    int priority;
    int opr;
    double num;
  };

  enum ErrorStates errorStatus_ = kOk;
  std::string inputStr_ = "";
  std::stack<DataSet> infixStack_;
  std::stack<DataSet> postfixStack_;
  double result_ = 0;

  // VALIDATOR
  void isCorrectNum(int& i);
  void isCorrectOperator(int& i, int& op);
  void initialCorrection();
  void isValid();
  int compareCharWithBinOps(const char target);
  int compareCharWithUnOps(const char target);
  void bracketsCase(int& i, int& bracketBalance);
  void operatorCase(int& i, int& op, int& ops, int& digit);
  void numCase(int& i, int& op, int& nums, int& digit);
  void checkErrors(int i, int op, int digit);

  // RPN_PARSER
  void pushOperator(const std::string& pInput, size_t& k);
  void reverseStack(std::stack<DataSet>& stack);
  int isOperator(unsigned char input);
  void pushOneSizeOperator(const std::string& pInput);
  void pushLargeSizeOperator(const std::string& pInput, size_t& k);
  void pushOtherOpsToRpnStack(std::stack<DataSet>& operStack, int& prev_token);
  void pullTillFlag(std::stack<DataSet>& operStack, int flag);
  void pushNumberToRpnStack(std::stack<DataSet>& operStack, int& prev_token);
  void popWithPush(std::stack<DataSet>& dest, std::stack<DataSet>& source);
  void pushMinusPlusToRpnStack(int& prev_token);
  void pushOperatorToRpnStack(std::stack<DataSet>& operStack, int prev_token);

  // RPN_CALC
  void binaryCalc(double dbArr[], int opr, int& i);
  void unaryCalc(double dbArr[], int opr, int& i);
  void oprCalc(int opr, double dbArr[], int& i);
  void applyUnOp(double a, int opr, double& middleResult);
  void applyBinOp(double a, double b, int opr, double& middleResult);
};

}  // namespace s21

#endif
