#ifndef CREDIT_MODEL_H
#define CREDIT_MODEL_H

#include <cmath>
#include <vector>

namespace s21 {

class CreditCalculatorModel {
 private:
  struct CreditData;
  struct CreditReport;

 public:
  CreditCalculatorModel() = default;
  CreditCalculatorModel(CreditData data);
  ~CreditCalculatorModel() = default;

  void creditCalculator();
  bool isEndOfMonths();
  std::vector<double> getReport();

 private:
  struct CreditData {
    double sum;
    int month;
    double creditRate;
    int isDiff;
  };

  struct CreditReport {
    double monthPayment;
    double overPayment;
    double totalPayment;
    int months;
  };
  CreditData crData_;
  CreditReport crReport_;
};

}  // namespace s21

#endif