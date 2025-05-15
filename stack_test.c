#include "f_stack.h"
#include <assert.h>

void test_is_empty() {
  stack_t stack;
  init_stack(&stack);
  assert(is_empty(&stack) == 1);
  assert(push(&stack, 10) == SUCCES);
  assert(is_empty(&stack) == 0);
}

void test_push() {
  stack_t stack;
  int flag;
  init_stack(&stack);
  assert(push(&stack, 10) == SUCCES);
  assert(stack.top == 0);
  assert(stack.data[0] == 10);
}

void test_pop() {
  stack_t stack;
  int flag;
  int elem;
  init_stack(&stack);
  flag = push(&stack, 10);
  assert(flag == SUCCES);

  flag = pop(&stack, &elem);
  assert(flag == SUCCES);
  assert(elem == 10);

  assert(is_empty(&stack));

  flag = pop(&stack, &elem);
  assert(flag == FAIL);
}

int main() {
  test_is_empty();
  test_push();
  test_pop();
  return 0;
}
