#include "s21_smart_calc.h"

stack *create_node(int priority, int opr, double number, stack *next) {
  stack *newNode = (stack *)calloc(1, sizeof(stack));
  if (newNode != NULL) {
    newNode->data.priority = priority;
    newNode->data.opr = opr;
    newNode->data.num = number;
    newNode->next = next;
  } else {
    fprintf(stderr, "Error in a node creating");
  }
  return newNode;
}

void push_node(stack **header, int priority, int opr, double number) {
  stack *newNode = create_node(priority, opr, number, NULL);
  newNode->next = *header;
  *header = newNode;
}

void pop_node(stack **header) {
  if (*header == NULL) {
    fprintf(stderr, "Error: node doesn't exist\n");
    return;
  }
  stack *tmp = *header;
  *header = (*header)->next;
  free(tmp);
}

void destroy_list(stack **header) {
  while (*header != NULL) {
    pop_node(header);
  }
  *header = NULL;
}