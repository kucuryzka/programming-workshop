#include "f_stack.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack(stack_t *stack) {
  stack->data = malloc(1 * sizeof(int));
  stack->top = -1;
  stack->capacity = 1;
}

int is_empty(stack_t *stack) { return stack->top == -1; }

int push(stack_t *stack, int value) {
  if (stack->top == stack->capacity - 1) {
    stack->capacity *= 2;
    stack->data = realloc(stack->data, stack->capacity * sizeof(int));
  }
  stack->data[++stack->top] = value;
  return SUCCES;
}

int pop(stack_t *stack, int *elem) {
  if (is_empty(stack)) {
    return FAIL;
  }

  *elem = stack->data[stack->top--];
  return SUCCES;
}
