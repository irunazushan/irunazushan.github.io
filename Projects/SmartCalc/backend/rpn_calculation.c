#include "s21_smart_calc.h"

int apply_bin_op(double a, double b, int opr, double *result) {
  int errorStatus = OK;
  if (opr == PLUS)
    *result = a + b;
  else if (opr == MINUS)
    *result = a - b;
  else if (opr == MULT)
    *result = a * b;
  else if (opr == DIV) {
    if (b != 0)
      *result = a / b;
    else
      errorStatus = DIV_BY_ZERO;
  } else if (opr == MOD) {
    *result = fmod(a, b);
    if (*result < 0) {
      *result += b;
    }
  } else if (opr == POW)
    *result = pow(a, b);
  return errorStatus;
}

int binary_calc(double *dbArr, int opr, int *i) {
  int errorStatus = OK;
  double tempRes = 0;
  errorStatus = apply_bin_op(dbArr[*i - 1], dbArr[*i], opr, &tempRes);
  dbArr[*i] = 0;
  dbArr[--(*i)] = tempRes;
  return errorStatus;
}

int apply_un_op(double a, int opr, double *result) {
  int errorStatus = OK;
  if ((opr == ASIN || opr == ACOS) && (a > 1.0 || a < -1.0))
    errorStatus = INVALID_ARG;
  else if (((opr == LOG || opr == LN) && (a <= 0)) || (opr == SQRT && (a < 0)))
    errorStatus = INVALID_ARG;

  if (errorStatus == OK) {
    if (opr == SQRT)
      *result = sqrt(a);
    else if (opr == SIN)
      *result = sin(a);
    else if (opr == COS)
      *result = cos(a);
    else if (opr == TAN)
      *result = tan(a);
    else if (opr == ACOS)
      *result = acos(a);
    else if (opr == ASIN)
      *result = asin(a);
    else if (opr == ATAN)
      *result = atan(a);
    else if (opr == LN)
      *result = log(a);
    else if (opr == LOG)
      *result = log10(a);
  }
  return errorStatus;
}

int unary_calc(double *dbArr, int opr, int *i) {
  int errorStatus = OK;
  double tempRes = 0;
  errorStatus = apply_un_op(dbArr[*i], opr, &tempRes);
  dbArr[*i] = tempRes;
  return errorStatus;
}

int opr_calc(int opr, double *dbArr, int *i) {
  int errorStatus = OK;
  if (opr >= PLUS && opr <= POW) {
    errorStatus = binary_calc(dbArr, opr, i);
  } else {
    errorStatus = unary_calc(dbArr, opr, i);
  }
  return errorStatus;
}

int calculation(stack **rpnStack, double *result, double x) {
  int errorStatus = OK;
  stack *temp = *rpnStack;
  double dbArr[128] = {0};
  int i = -1;
  while (temp != NULL && errorStatus == OK) {
    if (temp->data.priority == 0 && temp->data.opr == NUMBER) {
      dbArr[++i] = temp->data.num;
    } else if (temp->data.priority == 0 && temp->data.opr == X) {
      dbArr[++i] = x;
    }
    if (temp->data.priority > 0) {
      errorStatus = opr_calc(temp->data.opr, dbArr, &i);
    }
    temp = temp->next;
  }
  if (errorStatus == OK) {
    *result = dbArr[0];
  }
  return errorStatus;
}

int run_calc(char *inputString, double *result) {
  int errorStatus = run_validation(inputString);
  if (!errorStatus) {
    stack *rawStack = NULL;
    stack *rpnStack = NULL;
    expression_to_stack(inputString, &rawStack);
    rpn_stack(&rawStack, &rpnStack);
    errorStatus = calculation(&rpnStack, result, 0);
    destroy_list(&rawStack);
    destroy_list(&rpnStack);
  }
  return errorStatus;
}