#ifndef S21_SMART_CALC_H
#define S21_SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

enum options {
  NUMBER,
  X,
  PLUS,
  MINUS,
  MULT,
  DIV,
  MOD,
  POW,
  SQRT,
  SIN,
  COS,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  LN,
  LOG,
  UN_MINUS,
  UN_PLUS,
  OPEN_BRACKET,
  CLOSE_BRACKET,
  STOP_FLAG
};

enum err_st {
  OK,
  ERROR,
  OVER_SIZE,
  INCORRECT_OPERATOR,
  INCORRECT_BRACKETS,
  INCORRECT_NUMBER,
  DIV_BY_ZERO,
  INVALID_ARG
};

typedef struct {
  int priority;
  int opr;
  double num;
} data_set;

typedef struct Stack {
  data_set data;
  struct Stack* next;
} stack;

typedef struct creditData {
  double sum;
  int month;
  double creditRate;
  int isDiff;
} creditData;

typedef struct depositData {
  double depositSum;
  int fullPeriod;
  double percentageRate;
  double taxRate;
  double keyRate;
  int capitalization;
} depositData;

typedef struct Report {
  int period;
  double tax;
  double accruedCash;
  double cashFlow;
  double balance;
} Report;

// stack
stack* create_node(int priority, int opr, double number, stack* next);
void push_node(stack** header, int priority, int opr, double number);
void pop_node(stack** header);
void destroy_list(stack** header);

// RPN_PARSER
void push_operator(char** pInput, stack** head);
void reverse_stack(stack** head, stack** new_head);
void expression_to_stack(char* input, stack** head);
void rpn_stack(stack** rawStack, stack** rpnStack);
int is_operator(char input);

// RPN_CALC
int binary_calc(double* dbArr, int opr, int* i);
int unary_calc(double* dbArr, int opr, int* i);
int calculation(stack** rpnStack, double* result, double x);
int run_calc(char* inputString, double* result);

// VALIDATOR
int input_str(char* inputStr);
int is_correct_num(char* temp, int* i);
int is_correct_operator(char* temp, int* i, int* op);
void initial_correction(char* inputStr, char* freshedStr);
int is_valid(char* inputStr);
int run_validation(char* inputString);
char* get_error(int errorStatus);

// CREDIT_CALC
void credit_calculator(creditData crData, double* monthPayment,
                       double* overPayment, double* totalPayment, int* n);

// DEPOSIT_CALC
double calc_tax(double year_profit, double taxRate, double keyRate);
void deposit_calculator(depositData data, Report* report);

#endif
