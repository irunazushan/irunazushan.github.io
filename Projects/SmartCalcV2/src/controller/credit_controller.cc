#include "credit_controller.h"

namespace s21 {

CreditCalculatorController::CreditCalculatorController(CreditCalculatorModel* m)
    : model_(m){};

void CreditCalculatorController::runNextIteration() {
  model_->creditCalculator();
};

bool CreditCalculatorController::isEndOfIteration() {
  return model_->isEndOfMonths();
}

std::vector<double> CreditCalculatorController::getIterationReport() {
  return model_->getReport();
}

}  // namespace s21