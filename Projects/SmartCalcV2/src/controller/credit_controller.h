#ifndef CREDIT_CONTROLLER_H
#define CREDIT_CONTROLLER_H

#include <vector>

#include "../model/credit_model.h"

namespace s21 {

class CreditCalculatorController {
 public:
  CreditCalculatorController() = default;
  CreditCalculatorController(CreditCalculatorModel* m);
  ~CreditCalculatorController() = default;
  void runNextIteration();
  bool isEndOfIteration();
  std::vector<double> getIterationReport();

 private:
  CreditCalculatorModel* model_;
};

}  // namespace s21
#endif