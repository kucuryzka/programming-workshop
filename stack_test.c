#include "f_stack.h"
#include <assert.h>

void test_is_empty() {
  stack stakk;
  init_stack(&stakk);
  assert(is_empty(&stakk) == 1);
  push(&stakk, 10);
  assert(is_empty(&stakk) == 0);
}

void test_push() {
  stack stakk;
  init_stack(&stakk);
  push(&stakk, 10);
  assert(stakk.top == 0);
  assert(stakk.data[0] == 10);
}

void test_pop() {
  stack stakk;
  init_stack(&stakk);
  push(&stakk, 10);
  int popped = pop(&stakk);
  assert(popped == 10);
  assert(is_empty(&stakk));
}

int main() {
  test_is_empty();
  test_push();
  test_pop();
  return 0;
}
