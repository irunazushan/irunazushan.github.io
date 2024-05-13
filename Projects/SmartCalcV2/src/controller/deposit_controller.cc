#include "deposit_controller.h"

namespace s21 {

DepositCalculatorController::DepositCalculatorController(
    DepositCalculatorModel* m)
    : model_(m){};
void DepositCalculatorController::runNextIteration() {
  model_->depositCalculator();
};

bool DepositCalculatorController::isEndOfIteration() {
  return model_->isEndOfPeriod();
}

std::vector<double> DepositCalculatorController::getIterationReport() {
  return model_->getReport();
}

}  // namespace s21