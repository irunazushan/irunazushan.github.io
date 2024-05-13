#include "calculator_controller.h"

namespace s21 {

CalculatorController::CalculatorController(CalculatorModel* m) : model_(m){};

int CalculatorController::startCalculator(std::string exp, double x) {
  errorStatus_ = model_->runCalculator(exp, x);
  return errorStatus_;
}

int CalculatorController::getErrorStatus() { return errorStatus_; };

std::string CalculatorController::getErrorMessage() {
  return model_->getErrorMessage();
};

double CalculatorController::getResult() { return model_->getResult(); };

}  // namespace s21