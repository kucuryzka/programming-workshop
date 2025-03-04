#include "functions.h"

// фнукция вывода целочисленных корней
void print_integer_roots(Roots roots) {
  if (roots.count < 0) {
    printf("Error!\n");
  } else {
    printf("[");
    for (int i = 0; i < roots.count; i++) {
      if (roots.roots[i] == -0) {
        roots.roots[i] = 0;
      }
        printf("%g", roots.roots[i]); // вывод корней
    if (i < roots.count - 1) { // не последний элемент
      printf(", ");
      }
    }
    printf("]\n");
  }
}

// фнукция вывода вещественных корней
void print_real_roots(Roots roots, int decimal_point) {
  if (roots.count < 0) {
    printf("Error!\n");
  } else {
    printf("[");
    for (int i = 0; i < roots.count; i++) {
        printf("%.*f", decimal_point, roots.roots[i]); // вывод корней с * знаками после запятой
    if (i < roots.count - 1) { // не последний элемент
      printf(", ");
      }
    }
    printf("]\n");
  }
}

int main() {
  // Тест 1: a = 0
  printf("Test 1 (a = 0): ");
  Roots test1 = find_roots(0, 1, 1);
  print_integer_roots(test1);
  free_roots(test1);

  // Тест 2: a = 1, b = 0, c = -1
  printf("Test 2 (a = 1, b = 0, c = -1): ");
  Roots test2 = find_roots(1, 0, -1);
  print_integer_roots(test2);
  free_roots(test2);

  // Тест 3: a = 1, b = 0, c = 0
  printf("Test 3 (a = 1, b = 0, c = 0): ");
  Roots test3 = find_roots(1, 0, 0);
  print_integer_roots(test3);
  free_roots(test3);

  // Тест 4: a = 1, b = 0, c = 1
  printf("Test 4 (a = 1, b = 0, c = 1): ");
  Roots test4 = find_roots(1, 0, 1);
  print_integer_roots(test4);
  free_roots(test4);

  // Тест 5: a = 1, b = 0, c = -1E-7
  printf("Test 5 (a = 1, b = 0, c = -1E-7): ");
  Roots test5 = find_roots(1, 0, -1E-7);
  print_real_roots(test5, 4);
  free_roots(test5);

  // Тест 6: a = 1, b = -1E+10, c = -1
  printf("Test 6 (a = 1, b = -1E+10, c = -1): ");
  Roots test6 = find_roots(1, -1E+10, -1);
  print_real_roots(test6, 11);
  free_roots(test6);

  // Тест 7: a = 1, b = 0, c = -1E-8
  printf("Test 7 (a = 1, b = 0, c = -1E-8): ");
  Roots test7 = find_roots(1, 0, -1E-8);
  print_real_roots(test7, 7);
  free_roots(test7);
}