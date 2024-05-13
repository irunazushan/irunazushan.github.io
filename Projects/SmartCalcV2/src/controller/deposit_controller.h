#ifndef DEPOSIT_CONTROLLER_H
#define DEPOSIT_CONTROLLER_H

#include <vector>

#include "../model/deposit_model.h"

namespace s21 {

class DepositCalculatorController {
 public:
  DepositCalculatorController() = default;
  DepositCalculatorController(DepositCalculatorModel* m);
  ~DepositCalculatorController() = default;
  void runNextIteration();
  bool isEndOfIteration();
  std::vector<double> getIterationReport();

 private:
  DepositCalculatorModel* model_;
};

}  // namespace s21
#endif