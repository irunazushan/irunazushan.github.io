#ifndef DEPOSIT_MODEL_H
#define DEPOSIT_MODEL_H

#include <cmath>
#include <vector>

namespace s21 {
class DepositCalculatorModel {
 private:
  struct DepositData {
    double depositSum;
    int fullPeriod;
    double percentageRate;
    double taxRate;
    double keyRate;
    int capitalization;
  };

  struct DepositReport {
    double period;
    double tax;
    double accruedCash;
    double cashFlow;
    double balance;
  };

  DepositData dtData_;
  DepositReport dtReport_;

 public:
  DepositCalculatorModel() = default;
  DepositCalculatorModel(DepositData data);
  ~DepositCalculatorModel() = default;

  bool isEndOfPeriod();
  std::vector<double> getReport();
  double calcTax();
  void depositCalculator();
};

}  // namespace s21
#endif