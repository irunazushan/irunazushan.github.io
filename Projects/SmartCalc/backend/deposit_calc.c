#include "s21_smart_calc.h"

double calc_tax(double year_profit, double taxRate, double keyRate) {
  double tax;
  double taxFree = keyRate * 1e4;
  if (year_profit > 5 * 1e6) {
    tax = (year_profit - taxFree) * (taxRate + 2) / 100.0;
  } else {
    tax = (year_profit - taxFree) * (taxRate) / 100.0;
  }
  if (tax < 0) tax = 0;
  return tax;
}

void deposit_calculator(depositData data, Report* report) {
  if (data.capitalization == 0) {
    int currentPeriod = 0;
    if (data.fullPeriod - report->period >= 12) {
      currentPeriod = 12;
    } else {
      currentPeriod = (data.fullPeriod - report->period) % 12;
    }
    report->accruedCash =
        data.depositSum * (data.percentageRate / 100.0) * currentPeriod / 12;
    report->period += currentPeriod;
    report->tax = calc_tax(report->accruedCash, data.taxRate, data.keyRate);
    report->cashFlow = report->accruedCash - report->tax;
    report->balance += report->cashFlow;
  } else if (data.capitalization == 1) {
    int currentPeriod = 0;
    if (data.fullPeriod - report->period >= 12) {
      currentPeriod = 12;
    } else {
      currentPeriod = (data.fullPeriod - report->period) % 12;
    }
    report->accruedCash =
        (report->balance *
         pow((1 + data.percentageRate / 100.0 / 12), currentPeriod)) -
        report->balance;
    report->period += currentPeriod;
    report->tax = calc_tax(report->accruedCash, data.taxRate, data.keyRate);
    report->cashFlow = report->accruedCash - report->tax;
    report->balance += report->cashFlow;
  }
}