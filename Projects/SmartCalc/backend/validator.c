#include "s21_smart_calc.h"

int is_correct_num(char *temp, int *i) {
  int errorStatus = OK, dotCounter = 0;
  char *checker = temp;
  while ((isdigit(checker[*i]) || checker[*i] == '.') && errorStatus == OK) {
    if (checker[*i] == '.') {
      dotCounter++;
      if (!(dotCounter == 1 && isdigit(checker[*i + 1]))) {
        errorStatus = INCORRECT_NUMBER;
      }
    }
    (*i)++;
  }
  (*i)--;
  return errorStatus;
}

int is_correct_operator(char *temp, int *i, int *op) {
  *op = 0;
  int errorStatus = OK;
  char *checker = temp;
  if (ispunct(checker[*i])) {
    switch (checker[*i]) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
        *op = 2;
        break;
    }
  } else if (isalpha(checker[*i])) {
    size_t length = 0;
    char cmpBuff[5] = {0};
    for (length = 0; isalpha(checker[*i + length]) && errorStatus == OK;
         length++) {
      if (length < 4) {
        cmpBuff[length] = checker[*i + length];
      } else {
        errorStatus = INCORRECT_OPERATOR;
      }
    }
    if (errorStatus == OK) {
      cmpBuff[length] = '\0';
      char alphaOps[10][5] = {"mod",  "sin",  "cos",  "tan",  "log",
                              "acos", "asin", "atan", "sqrt", "ln"};
      for (int j = 0; j < 10; j++) {
        if (!strcmp(cmpBuff, alphaOps[j])) {
          *op = 1;
          (*i) += length - 1;
          break;
        }
      }
    }
  }
  if (!(*op)) errorStatus = INCORRECT_OPERATOR;
  return errorStatus;
}

int compare_char_with_bin_ops(char target) {
  int res = 0;
  char arr[] = {'/', '*', '^', 'm'};
  for (int i = 0; i < 4; i++) {
    if (target == arr[i]) {
      res = 1;
      break;
    }
  }
  return res;
}

int compare_char_with_un_ops(char target) {
  int res = 0;
  char arr[] = {'s', 'c', 't', 'l', 'a'};
  for (int i = 0; i < 5; i++) {
    if (target == arr[i]) {
      res = 1;
      break;
    }
  }
  return res;
}

void initial_correction(char *inputStr, char *freshedStr) {
  int j = 0, skip = 0;
  char ch = 0;
  for (int i = 0;
       (inputStr)[i] != '\n' && (inputStr)[i] != '=' && (inputStr)[i] != '\0';
       i++) {
    ch = (inputStr)[i];
    if (isalpha(ch))
      ch = tolower(ch);
    else if (isspace(ch))
      skip = 1;
    if (j > 0 && (freshedStr[j - 1] == '+' || freshedStr[j - 1] == '-') &&
        ch == '+')
      skip = 1;
    else if (j > 0 && freshedStr[j - 1] == '+' && ch == '-') {
      freshedStr[j - 1] = '-';
      skip = 1;
    } else if (j > 0 && freshedStr[j - 1] == '-' && ch == '-') {
      freshedStr[j - 1] = '+';
      skip = 1;
    }
    if (!skip) {
      freshedStr[j++] = ch;
    }
    skip = 0;
  }
  freshedStr[j] = '\0';
}

int brackets_case(char ch, int *opB, int *clB) {
  int errorStatus = OK;
  if (ch == '(')
    (*opB)++;
  else if (ch == ')') {
    (*clB)++;
  }
  if (*clB > *opB) {
    errorStatus = INCORRECT_BRACKETS;
  }
  return errorStatus;
}

int operator_case(char *temp, int *i, int *op, int *ops, int *digit) {
  int errorStatus = is_correct_operator(temp, i, op);
  *digit = 0;
  (*ops)++;
  return errorStatus;
}

int num_case(char *temp, int *i, int *op, int *nums, int *digit) {
  int errorStatus = OK;
  if (temp[*i] != 'x') {
    errorStatus = is_correct_num(temp, i);
  }
  *digit = 1;
  *op = 0;
  (*nums)++;
  return errorStatus;
}

void check_errors(char *temp, int i, int op, int digit, int *errorStatus) {
  if (op == 2 && (compare_char_with_bin_ops(temp[i]))) {
    *errorStatus = ERROR;
  } else if (digit == 1 && (compare_char_with_un_ops(temp[i]))) {
    *errorStatus = ERROR;
  }
}

int is_valid(char *inputStr) {
  if (inputStr == NULL) {
    return ERROR;
  }
  int errorStatus = OK, digit = 1, op = 1, nums = 0, ops = 0, i = 0, opB = 0,
      clB = 0;
  char temp[MAX_SIZE + 1];
  strncpy(temp, inputStr, MAX_SIZE + 1);
  if (compare_char_with_bin_ops(temp[0])) errorStatus = ERROR;

  while (temp[i] != '\n' && temp[i] != '=' && temp[i] != '\0' &&
         errorStatus == OK) {
    if (temp[i] == '(' || temp[i] == ')')
      errorStatus = brackets_case(temp[i], &opB, &clB);
    else if (is_operator(temp[i]) && errorStatus == OK)
      errorStatus = operator_case(temp, &i, &op, &ops, &digit);
    else if (op && (isdigit(temp[i]) || temp[i] == 'x') && errorStatus == OK)
      errorStatus = num_case(temp, &i, &op, &ops, &digit);
    else
      errorStatus = ERROR;
    if (errorStatus == OK) {
      i++;
      check_errors(temp, i, op, digit, &errorStatus);
    }
  }
  if (errorStatus == OK && (opB != clB)) errorStatus = INCORRECT_BRACKETS;
  if (errorStatus == OK && (op > nums)) errorStatus = ERROR;
  return errorStatus;
}

int run_validation(char *inputString) {
  if (inputString == NULL) {
    return ERROR;
  }
  size_t inputSize = strlen(inputString);
  int errorStatus = 0;
  if (inputSize <= MAX_SIZE) {
    char corrected[MAX_SIZE + 1] = {0};
    char forCpy[MAX_SIZE + 1] = {0};
    initial_correction(inputString, corrected);
    strcpy(forCpy, corrected);
    strcpy(inputString, forCpy);
    errorStatus = is_valid(inputString);
  } else {
    errorStatus = OVER_SIZE;
  }
  return errorStatus;
}

char *get_error(int errorStatus) {
  char *errorMessage = malloc(30 * sizeof(char));
  errorMessage[0] = '\0';
  if (errorStatus == ERROR)
    strcat(errorMessage, "ERROR\n");
  else if (errorStatus == INCORRECT_OPERATOR)
    strcat(errorMessage, "ERROR: INCORRECT_OPERATOR\n");
  else if (errorStatus == INCORRECT_BRACKETS)
    strcat(errorMessage, "ERROR: INCORRECT_BRACKETS\n");
  else if (errorStatus == INCORRECT_NUMBER)
    strcat(errorMessage, "ERROR: INCORRECT_NUMBER\n");
  else if (errorStatus == DIV_BY_ZERO)
    strcat(errorMessage, "ERROR: DIV_BY_ZERO\n");
  else if (errorStatus == INVALID_ARG)
    strcat(errorMessage, "ERROR: INVALID_ARG\n");
  else if (errorStatus == OVER_SIZE)
    strcat(errorMessage, "ERROR: OVER_SIZE\n");
  return errorMessage;
}