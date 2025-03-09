#include "functions.h"
#include <stdio.h>

int main() {
  stack stakk;
  init_stack(&stakk);

  push(&stakk, 23);
  push(&stakk, 53);
  push(&stakk, 31);
  printf("Содержание стека после вставки элементов: ");
  print_stack(&stakk);

  printf("Стек пуст? %s\n", is_empty(&stakk) ? "Да" : "Нет");

  int removed = pop(&stakk);
  printf("Удалённый элемент: %d\n", removed);

  return 0;
}
