#ifndef CALCULATOR_CONTROLLER_H
#define CALCULATOR_CONTROLLER_H

#include "../model/calculator_model.h"

namespace s21 {

class CalculatorController {
 public:
  CalculatorController() = default;
  CalculatorController(CalculatorModel* m);
  ~CalculatorController() = default;
  int startCalculator(std::string exp, double x = 0);
  int getErrorStatus();
  std::string getErrorMessage();
  double getResult();

 private:
  CalculatorModel* model_;
  int errorStatus_;
};

}  // namespace s21
#endif