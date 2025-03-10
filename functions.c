#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

// Функция для инициализации стека
void init_stack(stack *stakk) {
  stakk->data = malloc(1 * sizeof(int));
  stakk->top = -1;
  stakk->capacity = 1;
}

// Функция для проверки стека на пустоту
int is_empty(stack *stakk) { return stakk->top == -1; }

// Функция для вставки нового элемента в стек
void push(stack *stakk, int value) {
  if (stakk->top == stakk->capacity - 1) {
    stakk->capacity *= 2;
    stakk->data = realloc(stakk->data, stakk->capacity * sizeof(int));
  }
  stakk->data[++stakk->top] = value;
}

// Функция для удаления элемента из стека
int pop(stack *stakk) {
  if (is_empty(stakk)) {
    printf("Стек пуст. Невозможно удалить элемент.\n");
    return -1;
  }
  return stakk->data[stakk->top--];
}
