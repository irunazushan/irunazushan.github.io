#include "s21_smart_calc.h"

void push_one_size_operator(char **pInput, stack **head) {
  switch (**pInput) {
    case '+':
      push_node(head, 1, PLUS, 0);
      break;
    case '-':
      push_node(head, 1, MINUS, 0);
      break;
    case '*':
      push_node(head, 2, MULT, 0);
      break;
    case '/':
      push_node(head, 2, DIV, 0);
      break;
    case '^':
      push_node(head, 3, POW, 0);
      break;
    case '(':
      push_node(head, -2, OPEN_BRACKET, 0);
      break;
    case ')':
      push_node(head, -2, CLOSE_BRACKET, 0);
      break;
  }
}

void push_large_size_operator(char **pInput, stack **head) {
  size_t length = 0;
  for (length = 0; islower((*pInput)[length]); length++)
    ;
  char temp[length + 1];
  strncpy(temp, *pInput, length);
  temp[length] = '\0';
  if (!(strcmp(temp, "mod")))
    push_node(head, 2, MOD, 0);
  else if (!(strcmp(temp, "sin")))
    push_node(head, 4, SIN, 0);
  else if (!(strcmp(temp, "cos")))
    push_node(head, 4, COS, 0);
  else if (!(strcmp(temp, "tan")))
    push_node(head, 4, TAN, 0);
  else if (!(strcmp(temp, "log")))
    push_node(head, 4, LOG, 0);
  else if (!(strcmp(temp, "acos")))
    push_node(head, 4, ACOS, 0);
  else if (!(strcmp(temp, "asin")))
    push_node(head, 4, ASIN, 0);
  else if (!(strcmp(temp, "atan")))
    push_node(head, 4, ATAN, 0);
  else if (!(strcmp(temp, "sqrt")))
    push_node(head, 4, SQRT, 0);
  else if (!(strcmp(temp, "ln")))
    push_node(head, 4, LN, 0);
  *pInput += (length - 1);
}

void push_operator(char **pInput, stack **head) {
  if (ispunct(**pInput)) {
    push_one_size_operator(pInput, head);
  } else if (islower(**pInput)) {
    push_large_size_operator(pInput, head);
  }
}

int is_operator(char input) {
  return ((ispunct(input) || islower(input)) && input != 'x');
}

void reverse_stack(stack **head, stack **new_head) {
  stack *temp = *head;
  while (temp != NULL) {
    push_node(new_head, temp->data.priority, temp->data.opr, temp->data.num);
    temp = temp->next;
  }
  destroy_list(head);
  *head = *new_head;
}

void expression_to_stack(char *input, stack **head) {
  char *pInput = input;
  while (*pInput != '=' && *pInput != '\n' && *pInput != '\0') {
    if (isdigit(*pInput)) {
      push_node(head, 0, NUMBER, strtod(pInput, &pInput));
      continue;
    } else if (*pInput == 'x') {
      push_node(head, 0, X, 0);
    } else if (is_operator(*pInput)) {
      push_operator(&pInput, head);
    }
    pInput++;
  }
  stack *new_head = NULL;
  reverse_stack(head, &new_head);
}

void pull_till_flag(stack **rpnStack, stack **operStack, int flag) {
  if (flag != STOP_FLAG) {
    while ((*operStack)->data.opr != flag) {
      push_node(rpnStack, (*operStack)->data.priority, (*operStack)->data.opr,
                (*operStack)->data.num);
      pop_node(operStack);
    }
    pop_node(operStack);
  } else {
    while ((*operStack) != NULL) {
      push_node(rpnStack, (*operStack)->data.priority, (*operStack)->data.opr,
                (*operStack)->data.num);
      pop_node(operStack);
    }
  }
}

void pop_with_push(stack **dest, stack **source) {
  push_node(dest, (*source)->data.priority, (*source)->data.opr,
            (*source)->data.num);
  pop_node(source);
}

void push_number_to_rpn_stack(stack **rpnStack, stack **operStack, stack *temp,
                              int *prev_token) {
  push_node(rpnStack, temp->data.priority, temp->data.opr, temp->data.num);
  if (*prev_token == UN_MINUS || *prev_token == UN_PLUS) {
    pop_with_push(rpnStack, operStack);
    *prev_token = 0;
  }
}

void push_minus_plus_to_rpn_stack(stack **rpnStack, stack *temp,
                                  int *prev_token) {
  if (*prev_token == UN_MINUS || *prev_token == UN_PLUS) *prev_token = 0;
  if ((temp->data.opr == MINUS || temp->data.opr == PLUS) &&
      (*prev_token == -1 || *prev_token == OPEN_BRACKET ||
       (*prev_token >= PLUS && *prev_token <= POW))) {
    push_node(rpnStack, 0, 0, 0);
    if (temp->data.opr == MINUS)
      *prev_token = UN_MINUS;
    else if (temp->data.opr == PLUS)
      *prev_token = UN_PLUS;
  }
}

void push_other_ops_to_rpn_stack(stack **rpnStack, stack **operStack,
                                 stack *temp, int *prev_token) {
  if (*operStack == NULL)
    *operStack =
        create_node(temp->data.priority, temp->data.opr, temp->data.num, NULL);
  else if (temp->data.opr == CLOSE_BRACKET)
    pull_till_flag(rpnStack, operStack, OPEN_BRACKET);
  else if (temp->data.opr == OPEN_BRACKET)
    push_node(operStack, temp->data.priority, temp->data.opr, temp->data.num);
  else if (*prev_token == UN_MINUS || *prev_token == UN_PLUS)
    push_node(operStack, temp->data.priority, temp->data.opr, temp->data.num);
  else if ((*operStack)->data.priority >= temp->data.priority) {
    while (*operStack != NULL &&
           (*operStack)->data.priority >= temp->data.priority) {
      pop_with_push(rpnStack, operStack);
    }
    push_node(operStack, temp->data.priority, temp->data.opr, temp->data.num);
  } else if ((*operStack)->data.priority < temp->data.priority)
    push_node(operStack, temp->data.priority, temp->data.opr, temp->data.num);
}

void push_operator_to_rpn_stack(stack **rpnStack, stack **operStack,
                                stack *temp, int *prev_token) {
  push_minus_plus_to_rpn_stack(rpnStack, temp, prev_token);
  push_other_ops_to_rpn_stack(rpnStack, operStack, temp, prev_token);
}

void rpn_stack(stack **rawStack, stack **rpnStack) {
  stack *temp = *rawStack;
  stack *operStack = NULL;
  int prev_token = -1;
  while (temp != NULL) {
    if (temp->data.priority == 0) {
      push_number_to_rpn_stack(rpnStack, &operStack, temp, &prev_token);
    } else {
      push_operator_to_rpn_stack(rpnStack, &operStack, temp, &prev_token);
    }
    if (prev_token != UN_MINUS && prev_token != UN_PLUS)
      prev_token = temp->data.opr;
    temp = temp->next;
  }
  pull_till_flag(rpnStack, &operStack, STOP_FLAG);
  stack *reversedStack = NULL;
  reverse_stack(rpnStack, &reversedStack);
  destroy_list(&operStack);
}