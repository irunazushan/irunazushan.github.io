#include "credit_model.h"

namespace s21 {

CreditCalculatorModel::CreditCalculatorModel(CreditData data)
    : crData_(data), crReport_({0, 0, 0, 0}) {}

void CreditCalculatorModel::creditCalculator() {
  if (!crData_.isDiff) {
    double anFactor, monthlyPercentage;
    monthlyPercentage = (crData_.creditRate / 12.0) / 100.0;
    anFactor = monthlyPercentage * pow((1 + monthlyPercentage), crData_.month) /
               ((pow((1 + monthlyPercentage), crData_.month) - 1));
    crReport_.monthPayment = anFactor * crData_.sum;
    crReport_.totalPayment = crReport_.monthPayment * crData_.month;
    crReport_.overPayment = crReport_.totalPayment - crData_.sum;
    crReport_.months = crData_.month;
  } else if (crData_.isDiff) {
    double creditBody = crData_.sum / crData_.month;
    double leftPayment = crData_.sum - (creditBody * crReport_.months);
    double percentagePayment =
        leftPayment * (crData_.creditRate / 12.0) / 100.0;
    crReport_.monthPayment = creditBody + percentagePayment;
    crReport_.totalPayment += crReport_.monthPayment;
    if (crReport_.months == crData_.month - 1) {
      crReport_.overPayment = crReport_.totalPayment - crData_.sum;
    }
    ++crReport_.months;
  }
}

bool CreditCalculatorModel::isEndOfMonths() {
  return crReport_.months < crData_.month;
}

std::vector<double> CreditCalculatorModel::getReport() {
  std::vector<double> report = {crReport_.monthPayment, crReport_.overPayment,
                                crReport_.totalPayment};
  return report;
}

}  // namespace s21