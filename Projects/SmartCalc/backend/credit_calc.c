#include "s21_smart_calc.h"

void credit_calculator(creditData crData, double* monthPayment,
                       double* overPayment, double* totalPayment, int* n) {
  if (!crData.isDiff) {
    double anFactor, monthlyPercentage;
    monthlyPercentage = (crData.creditRate / 12.0) / 100.0;
    anFactor = monthlyPercentage * pow((1 + monthlyPercentage), crData.month) /
               ((pow((1 + monthlyPercentage), crData.month) - 1));
    *monthPayment = anFactor * crData.sum;
    *totalPayment = *monthPayment * crData.month;
    *overPayment = *totalPayment - crData.sum;
    *n = crData.month;
  } else if (crData.isDiff) {
    double creditBody = crData.sum / crData.month;
    double leftPayment = crData.sum - (creditBody * *n);
    double percentagePayment = leftPayment * (crData.creditRate / 12.0) / 100.0;
    *monthPayment = creditBody + percentagePayment;
    *totalPayment += *monthPayment;
    if (*n == crData.month - 1) {
      *overPayment = *totalPayment - crData.sum;
    }
    (*n)++;
  }
}
