#include "f_stack.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack(stack *stakk) {
  stakk->data = malloc(1 * sizeof(int));
  stakk->top = -1;
  stakk->capacity = 1;
}

int is_empty(stack *stakk) { return stakk->top == -1; }

void push(stack *stakk, int value, int *flag) {
  if (stakk->top == stakk->capacity - 1) {
    stakk->capacity *= 2;
    stakk->data = realloc(stakk->data, stakk->capacity * sizeof(int));
  }
  stakk->data[++stakk->top] = value;
  *flag = SUCCES;
}

int pop(stack *stakk, int *flag) {
  if (is_empty(stakk)) {
    *flag = FAIL;
    return -1;
  }

  *flag = SUCCES;
  return stakk->data[stakk->top--];
}
