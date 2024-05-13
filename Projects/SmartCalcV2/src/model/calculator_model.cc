#include "calculator_model.h"

namespace s21 {

// VALIDATOR

void CalculatorModel::isCorrectNum(int& i) {
  int dotCounter = 0, flagE = 0;
  while ((std::isdigit(static_cast<unsigned char>(inputStr_[i])) ||
          inputStr_[i] == '.' || (inputStr_[i] == 'e')) &&
         errorStatus_ == kOk) {
    if (inputStr_[i] == '.') {
      ++dotCounter;
      if (flagE || !(dotCounter == 1 && std::isdigit(static_cast<unsigned char>(
                                            inputStr_[i + 1])))) {
        errorStatus_ = kIncorrectNumber;
      }
    }
    if (inputStr_[i] == 'e') {
      if ((inputStr_[i + 1] == '+' || inputStr_[i + 1] == '-') &&
          (std::isdigit(static_cast<unsigned char>(inputStr_[i + 2])))) {
        flagE = 1;
        i += 2;
      } else {
        errorStatus_ = kIncorrectNumber;
      }
    }
    ++i;
  }
  --i;
}

void CalculatorModel::isCorrectOperator(int& i, int& op) {
  op = 0;
  char currentChar = inputStr_[i];
  if (std::ispunct(static_cast<unsigned char>(currentChar))) {
    switch (currentChar) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
        op = 2;
        break;
    }
  } else if (std::isalpha(static_cast<unsigned char>(currentChar))) {
    std::string operatorStr;
    for (size_t length = 0; length < 4; ++length) {
      char nextChar = inputStr_[i + length];
      if (std::isalpha(static_cast<unsigned char>(nextChar))) {
        operatorStr += nextChar;
      } else {
        break;
      }
    }
    if (errorStatus_ == kOk) {
      std::string alphaOps[10] = {"mod",  "sin",  "cos",  "tan",  "log",
                                  "acos", "asin", "atan", "sqrt", "ln"};
      for (int j = 0; j < 10; j++) {
        if (operatorStr == alphaOps[j]) {
          op = 1;
          i += operatorStr.size() - 1;
          break;
        }
      }
    }
  }
}

int CalculatorModel::compareCharWithBinOps(const char target) {
  int res = 0;
  char arr[] = {'/', '*', '^', 'm'};
  for (int i = 0; i < 4; ++i) {
    if (target == arr[i]) {
      res = 1;
      break;
    }
  }
  return res;
}

int CalculatorModel::compareCharWithUnOps(const char target) {
  int res = 0;
  char arr[] = {'s', 'c', 't', 'l', 'a'};
  for (int i = 0; i < 5; ++i) {
    if (target == arr[i]) {
      res = 1;
      break;
    }
  }
  return res;
}

void CalculatorModel::initialCorrection() {
  std::string freshedStr;
  int j = 0, skip = 0;
  unsigned char ch = 0;
  for (int i = 0; (inputStr_)[i] != '\n' && (inputStr_)[i] != '=' &&
                  (inputStr_)[i] != '\0';
       ++i) {
    ch = static_cast<unsigned char>((inputStr_)[i]);
    if (std::isalpha(ch))
      ch = std::tolower(ch);
    else if (std::isspace(ch))
      skip = 1;
    if (j > 0 && (freshedStr[j - 1] == '+' || freshedStr[j - 1] == '-') &&
        ch == '+')
      skip = 1;
    else if (j > 0 && freshedStr[j - 1] == '+' && ch == '-') {
      freshedStr[j - 1] = '-';
      skip = 1;
    } else if (j > 0 && freshedStr[j - 1] == '-' && ch == '-') {
      freshedStr[j - 1] = '+';
      skip = 1;
    }
    if (!skip) {
      freshedStr += ch;
      ++j;
    }
    skip = 0;
  }
  inputStr_.clear();
  inputStr_ = freshedStr;
}

void CalculatorModel::bracketsCase(int& i, int& bracketBalance) {
  if (i > 0 && inputStr_[i - 1] == '(' && inputStr_[i] == ')') {
    errorStatus_ = kEmptyBrackets;
    return;
  }
  if (inputStr_[i] == '(')
    ++bracketBalance;
  else if (inputStr_[i] == ')') {
    --bracketBalance;
  }
  if (bracketBalance < 0) {
    errorStatus_ = kIncorrectBrackets;
  }
}

void CalculatorModel::operatorCase(int& i, int& op, int& ops, int& digit) {
  isCorrectOperator(i, op);
  if (op == 0)
    errorStatus_ = kIncorrectOperator;
  else if (op == 1 && inputStr_[i] != 'd' && inputStr_[i + 1] != '(')
    errorStatus_ = kIncorrectBrackets;
  else if (i > 0 && op == 2 && (inputStr_[i] != '+' && inputStr_[i] != '-') &&
           inputStr_[i - 1] == '(')
    errorStatus_ = kError;
  else if (i > 3 && op == 1 && (inputStr_[i] == 'd') && inputStr_[i - 3] == '(')
    errorStatus_ = kError;
  digit = 0;
  ++ops;
}

void CalculatorModel::numCase(int& i, int& op, int& nums, int& digit) {
  if (inputStr_[i] != 'x') {
    isCorrectNum(i);
  }
  digit = 1;
  op = 0;
  ++nums;
}

void CalculatorModel::checkErrors(int i, int op, int digit) {
  if (op == 2 && (compareCharWithBinOps(inputStr_[i]))) {
    errorStatus_ = kError;
  } else if (digit == 1 && (compareCharWithUnOps(inputStr_[i]))) {
    errorStatus_ = kError;
  }
}

int CalculatorModel::isOperator(unsigned char input) {
  return ((std::ispunct(input) || std::isalpha(input)) && input != 'x' &&
          input != 'e');
}

void CalculatorModel::isValid() {
  if (inputStr_.size() == 0 || inputStr_.size() >= MAX_SIZE + 1) {
    errorStatus_ = kError;
    return;
  }
  int digit = 1, op = 1, nums = 0, ops = 0, i = 0, bracketBalance = 0;
  if (compareCharWithBinOps(inputStr_[0])) errorStatus_ = kError;
  while (static_cast<size_t>(i) < inputStr_.size() && errorStatus_ == kOk) {
    if (inputStr_[i] == '(' || inputStr_[i] == ')') {
      bracketsCase(i, bracketBalance);
    } else if (isOperator(inputStr_[i]) && errorStatus_ == kOk) {
      operatorCase(i, op, ops, digit);
    } else if (op &&
               (std::isdigit(static_cast<unsigned char>(inputStr_[i])) ||
                inputStr_[i] == 'x') &&
               errorStatus_ == kOk)
      numCase(i, op, ops, digit);
    else
      errorStatus_ = kError;
    if (errorStatus_ == kOk) {
      ++i;
      checkErrors(i, op, digit);
    }
  }
  if (errorStatus_ == kOk && (bracketBalance != 0))
    errorStatus_ = kIncorrectBrackets;
  if (errorStatus_ == kOk && (op > nums)) errorStatus_ = kError;
}

void CalculatorModel::runValidation(std::string& inputString) {
  inputStr_ = inputString;
  if (inputString.size() == 0) {
    errorStatus_ = kError;
    return;
  }
  size_t inputSize = inputString.size();
  if (inputSize <= MAX_SIZE) {
    initialCorrection();
    isValid();
  } else {
    errorStatus_ = kOverSize;
  }
}

std::string CalculatorModel::getErrorMessage() {
  std::string errorMessage;
  errorMessage = '\0';
  if (errorStatus_ == kError)
    errorMessage = "ERROR\n";
  else if (errorStatus_ == kIncorrectOperator)
    errorMessage = "ERROR: Incorrect Operator\n";
  else if (errorStatus_ == kIncorrectBrackets)
    errorMessage = "ERROR: Incorrect Brackets\n";
  else if (errorStatus_ == kIncorrectNumber)
    errorMessage = "ERROR: Incorrect Number\n";
  else if (errorStatus_ == kDivByZero)
    errorMessage = "ERROR: Div by Zero\n";
  else if (errorStatus_ == kInvalidArg)
    errorMessage = "ERROR: Invalid Arg\n";
  else if (errorStatus_ == kOverSize)
    errorMessage = "ERROR: Over Size\n";
  else if (errorStatus_ == kEmptyBrackets)
    errorMessage = "ERROR: Empty Brackets\n";
  return errorMessage;
}

// RPN_PARSER

void CalculatorModel::pushOneSizeOperator(const std::string& pInput) {
  switch (pInput[0]) {
    case '+':
      infixStack_.push({1, kPlus, 0});
      break;
    case '-':
      infixStack_.push({1, kMinus, 0});
      break;
    case '*':
      infixStack_.push({2, kMult, 0});
      break;
    case '/':
      infixStack_.push({2, kDiv, 0});
      break;
    case '^':
      infixStack_.push({3, kPow, 0});
      break;
    case '(':
      infixStack_.push({-2, kOpenBracket, 0});
      break;
    case ')':
      infixStack_.push({-2, kCloseBracket, 0});
      break;
  }
}

void CalculatorModel::pushLargeSizeOperator(const std::string& pInput,
                                            size_t& k) {
  size_t length = 0;
  for (length = 0; std::islower((pInput)[length]); length++)
    ;
  std::string temp;
  temp = pInput.substr(0, length);
  if (temp == "mod")
    infixStack_.push({2, kMod, 0});
  else if (temp == "sin")
    infixStack_.push({4, kSin, 0});
  else if (temp == "cos")
    infixStack_.push({4, kCos, 0});
  else if (temp == "tan")
    infixStack_.push({4, kTan, 0});
  else if (temp == "log")
    infixStack_.push({4, kLog, 0});
  else if (temp == "acos")
    infixStack_.push({4, kAcos, 0});
  else if (temp == "asin")
    infixStack_.push({4, kAsin, 0});
  else if (temp == "atan")
    infixStack_.push({4, kAtan, 0});
  else if (temp == "sqrt")
    infixStack_.push({4, kSqrt, 0});
  else if (temp == "ln")
    infixStack_.push({4, kLn, 0});
  k += (length - 1);
}

void CalculatorModel::pushOperator(const std::string& pInput, size_t& k) {
  size_t upK = 0;
  if (std::ispunct(static_cast<unsigned char>(pInput[upK]))) {
    pushOneSizeOperator(pInput);
  } else if (std::islower(static_cast<unsigned char>(pInput[upK]))) {
    pushLargeSizeOperator(pInput, upK);
  }
  k += upK;
}

void CalculatorModel::reverseStack(std::stack<DataSet>& stack) {
  std::stack<DataSet> infixStack_ = stack;
  std::stack<DataSet> new_infixStack_;
  while (infixStack_.size() != 0) {
    new_infixStack_.push(infixStack_.top());
    infixStack_.pop();
  }
  stack = new_infixStack_;
}

void CalculatorModel::expressionToStack() {
  size_t k = 0;
  size_t upK = 0;
  while (k <= inputStr_.size()) {
    if (std::isdigit(static_cast<unsigned char>(inputStr_[k]))) {
      infixStack_.push({0, kNumber,
                        std::stod(inputStr_.substr(k),
                                  &upK)});  // возможно будут проблемки с strtod
      k += upK;
      continue;
    } else if (inputStr_[k] == 'x') {
      infixStack_.push({0, kX, 0});
    } else if (isOperator(static_cast<unsigned char>((inputStr_[k])))) {
      pushOperator(inputStr_.substr(k), k);
    }
    ++k;
  }
  reverseStack(infixStack_);
}

void CalculatorModel::pullTillFlag(std::stack<DataSet>& operStack, int flag) {
  if (flag != kStopFlag) {
    while (operStack.top().opr != flag) {
      postfixStack_.push(
          {operStack.top().priority, operStack.top().opr, operStack.top().num});
      operStack.pop();
    }
    operStack.pop();
  } else {
    while (operStack.size() != 0) {
      postfixStack_.push(
          {operStack.top().priority, operStack.top().opr, operStack.top().num});
      operStack.pop();
    }
  }
}

void CalculatorModel::popWithPush(std::stack<DataSet>& dest,
                                  std::stack<DataSet>& source) {
  dest.push({source.top().priority, source.top().opr, source.top().num});
  source.pop();
}

void CalculatorModel::pushNumberToRpnStack(std::stack<DataSet>& operStack,
                                           int& prevToken) {
  postfixStack_.push(infixStack_.top());
  if (prevToken == kUnMinus || prevToken == kUnPlus) {
    popWithPush(postfixStack_, operStack);
    prevToken = 0;
  }
}

void CalculatorModel::pushMinusPlusToRpnStack(int& prevToken) {
  if (prevToken == kUnMinus || prevToken == kUnPlus) prevToken = 0;
  if ((infixStack_.top().opr == kMinus || infixStack_.top().opr == kPlus) &&
      (prevToken == -1 || prevToken == kOpenBracket ||
       (prevToken >= kPlus && prevToken <= kPow))) {
    postfixStack_.push({0, 0, 0});
    if (infixStack_.top().opr == kMinus)
      prevToken = kUnMinus;
    else if (infixStack_.top().opr == kPlus)
      prevToken = kUnPlus;
  }
}

void CalculatorModel::pushOtherOpsToRpnStack(std::stack<DataSet>& operStack,
                                             int& prevToken) {
  auto currentCell = infixStack_.top();
  if (operStack.size() == 0)
    operStack.push(currentCell);
  else if (currentCell.opr == kCloseBracket)
    pullTillFlag(operStack, kOpenBracket);
  else if (currentCell.opr == kOpenBracket)
    operStack.push(currentCell);
  else if (prevToken == kUnMinus || prevToken == kUnPlus)
    operStack.push(currentCell);
  else if (operStack.top().priority >= currentCell.priority) {
    while (operStack.size() != 0 &&
           operStack.top().priority >= currentCell.priority) {
      popWithPush(postfixStack_, operStack);
    }
    operStack.push(currentCell);
  } else if (operStack.top().priority < currentCell.priority)
    operStack.push(currentCell);
}

void CalculatorModel::pushOperatorToRpnStack(std::stack<DataSet>& operStack,
                                             int prevToken) {
  pushMinusPlusToRpnStack(prevToken);
  pushOtherOpsToRpnStack(operStack, prevToken);
}

void CalculatorModel::convertStackToRpnStack() {
  std::stack<DataSet> operStack;
  int prevToken = -1;
  while (infixStack_.size() != 0) {
    if (infixStack_.top().priority == 0) {
      pushNumberToRpnStack(operStack, prevToken);
    } else {
      pushOperatorToRpnStack(operStack, prevToken);
    }
    if (prevToken != kUnMinus && prevToken != kUnPlus)
      prevToken = infixStack_.top().opr;
    infixStack_.pop();
  }
  pullTillFlag(operStack, kStopFlag);
  reverseStack(postfixStack_);
}

// RPN_CALC

void CalculatorModel::applyBinOp(double a, double b, int opr,
                                 double& middleResult) {
  if (opr == kPlus)
    middleResult = a + b;
  else if (opr == kMinus)
    middleResult = a - b;
  else if (opr == kMult)
    middleResult = a * b;
  else if (opr == kDiv) {
    if (b != 0)
      middleResult = a / b;
    else
      errorStatus_ = kDivByZero;
  } else if (opr == kMod) {
    middleResult = fmod(a, b);
    if (middleResult < 0) {
      middleResult += b;
    }
  } else if (opr == kPow)
    middleResult = pow(a, b);
}

void CalculatorModel::binaryCalc(double dbArr[], int opr, int& i) {
  double infixStack_Res = 0;
  applyBinOp(dbArr[i - 1], dbArr[i], opr, infixStack_Res);
  dbArr[i] = 0;
  dbArr[--i] = infixStack_Res;
}

void CalculatorModel::applyUnOp(double a, int opr, double& middleResult) {
  if ((opr == kAsin || opr == kAcos) && (a > 1.0 || a < -1.0))
    errorStatus_ = kInvalidArg;
  else if (((opr == kLog || opr == kLn) && (a <= 0)) ||
           (opr == kSqrt && (a < 0)))
    errorStatus_ = kInvalidArg;

  if (errorStatus_ == kOk) {
    if (opr == kSqrt)
      middleResult = sqrt(a);
    else if (opr == kSin)
      middleResult = sin(a);
    else if (opr == kCos)
      middleResult = cos(a);
    else if (opr == kTan)
      middleResult = tan(a);
    else if (opr == kAcos)
      middleResult = acos(a);
    else if (opr == kAsin)
      middleResult = asin(a);
    else if (opr == kAtan)
      middleResult = atan(a);
    else if (opr == kLn)
      middleResult = log(a);
    else if (opr == kLog)
      middleResult = log10(a);
  }
}

void CalculatorModel::unaryCalc(double dbArr[], int opr, int& i) {
  double infixStack_Res = 0;
  applyUnOp(dbArr[i], opr, infixStack_Res);
  dbArr[i] = infixStack_Res;
}

void CalculatorModel::oprCalc(int opr, double dbArr[], int& i) {
  if (opr >= kPlus && opr <= kPow) {
    binaryCalc(dbArr, opr, i);
  } else {
    unaryCalc(dbArr, opr, i);
  }
}

void CalculatorModel::calculation(double x) {
  double dbArr[128] = {0};
  int i = -1;
  while (postfixStack_.size() != 0 && errorStatus_ == kOk) {
    auto currentCell = postfixStack_.top();
    if (currentCell.priority == 0 && currentCell.opr == kNumber) {
      dbArr[++i] = currentCell.num;
    } else if (currentCell.priority == 0 && currentCell.opr == kX) {
      dbArr[++i] = x;
    }
    if (currentCell.priority > 0) {
      oprCalc(currentCell.opr, dbArr, i);
    }
    postfixStack_.pop();
  }
  if (errorStatus_ == kOk) {
    result_ = dbArr[0];
  }
}

double CalculatorModel::getResult() { return result_; }

void CalculatorModel::clean() {
  errorStatus_ = kOk;
  result_ = 0;
  while (!infixStack_.empty()) {
    infixStack_.pop();
  }
  while (!postfixStack_.empty()) {
    postfixStack_.pop();
  }
}

int CalculatorModel::getError() { return errorStatus_; }

int CalculatorModel::runCalculator(std::string& expression, double x) {
  clean();
  runValidation(expression);
  if (getError() == kOk) {
    expressionToStack();
    convertStackToRpnStack();
    calculation(x);
  }
  return errorStatus_;
}

}  // namespace s21