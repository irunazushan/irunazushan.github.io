#include "deposit_model.h"

namespace s21 {

DepositCalculatorModel::DepositCalculatorModel(DepositData data)
    : dtData_(data), dtReport_({0, 0, 0, 0, dtData_.depositSum}) {}

bool DepositCalculatorModel::isEndOfPeriod() {
  return dtReport_.period < dtData_.fullPeriod;
}

std::vector<double> DepositCalculatorModel::getReport() {
  std::vector<double> report{dtReport_.balance, dtReport_.tax,
                             dtReport_.cashFlow, dtReport_.accruedCash,
                             dtReport_.period};
  return report;
}

double DepositCalculatorModel::calcTax() {
  double year_profit = dtReport_.accruedCash;
  double tax;
  double taxFree = dtData_.keyRate * 1e4;
  if (year_profit > 5 * 1e6) {
    tax = (year_profit - taxFree) * (dtData_.taxRate + 2) / 100.0;
  } else {
    tax = (year_profit - taxFree) * (dtData_.taxRate) / 100.0;
  }
  if (tax < 0) tax = 0;
  return tax;
}

void DepositCalculatorModel::depositCalculator() {
  if (dtData_.capitalization == 0) {
    int currentPeriod = 0;
    if (dtData_.fullPeriod - dtReport_.period >= 12) {
      currentPeriod = 12;
    } else {
      currentPeriod =
          static_cast<int>((dtData_.fullPeriod - dtReport_.period)) % 12;
    }
    dtReport_.accruedCash = dtData_.depositSum *
                            (dtData_.percentageRate / 100.0) * currentPeriod /
                            12;
    dtReport_.period += currentPeriod;
    dtReport_.tax = calcTax();
    dtReport_.cashFlow = dtReport_.accruedCash - dtReport_.tax;
    dtReport_.balance += dtReport_.cashFlow;
  } else if (dtData_.capitalization == 1) {
    int currentPeriod = 0;
    if (dtData_.fullPeriod - dtReport_.period >= 12) {
      currentPeriod = 12;
    } else {
      currentPeriod =
          static_cast<int>((dtData_.fullPeriod - dtReport_.period)) % 12;
    }
    dtReport_.accruedCash =
        (dtReport_.balance *
         pow((1 + dtData_.percentageRate / 100.0 / 12), currentPeriod)) -
        dtReport_.balance;
    dtReport_.period += currentPeriod;
    dtReport_.tax = calcTax();
    dtReport_.cashFlow = dtReport_.accruedCash - dtReport_.tax;
    dtReport_.balance += dtReport_.cashFlow;
  }
}

}  // namespace s21