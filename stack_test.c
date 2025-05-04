#include "f_stack.h"
#include <assert.h>

void test_is_empty() {
  stack stakk;
  int flag;
  init_stack(&stakk);
  assert(is_empty(&stakk) == 1);
  push(&stakk, 10, &flag);
  assert(is_empty(&stakk) == 0);
}

void test_push() {
  stack stakk;
  int flag;
  init_stack(&stakk);
  push(&stakk, 10, &flag);
  assert(stakk.top == 0);
  assert(stakk.data[0] == 10);
}

void test_pop() {
  stack stakk;
  int flag;
  init_stack(&stakk);
  push(&stakk, 10, &flag);
  int popped = pop(&stakk, &flag);
  assert(popped == 10);
  assert(is_empty(&stakk) && flag == SUCCES);

  int popped2 = pop(&stakk, &flag);
  assert(flag == 0);
}

int main() {
  test_is_empty();
  test_push();
  test_pop();
  return 0;
}
