#include "functions.h"
#include <assert.h>

void test_linear_equation() {
  double* result = finding_roots_quadratic_equation(0, 0, 0, 1e-9);
  assert(result == NULL);
  free(result);
}

void test_x_squared_minus_one() {
  double* result = finding_roots_quadratic_equation(1, 0, -1, 1e-12);
  double answer[2] = {-1.0, 1.0};
  assert(fabs(result[0] - answer[0]) < 1e-12 && fabs(result[1] - answer[1]) < 1e-12);
  free(result);
}

void test_x_squared() {
  double* result = finding_roots_quadratic_equation(1, 0, 0, 1e-9);
  double answer[1] = {0};
  assert(fabs(result[0] - answer[0]) < 1e-9);
  free(result);
}

void test_x_squared_plus_one() {
  double* result = finding_roots_quadratic_equation(1, 0, 1, 1e-9);
  assert(result == NULL);
  free(result);
}

void test_x_squared_minus_one_ten_millionth() {
  double* result = finding_roots_quadratic_equation(1, 0, -1e-7, 1e-9);
  double answer[2] = {-sqrt(1e-7), sqrt(1e-7)};
  assert(fabs(result[0] - answer[0]) < 1E-4 && fabs(result[1] - answer[1]) < 1E-4);
  free(result);
}

void test_x_squared_minus_ten_billion_x_minus_one() {
  double* result = finding_roots_quadratic_equation(1, -1e+10, -1, 1e-11);
  double answer[2] = {-1e-10, 1e+10};
  assert(fabs(result[0] - answer[0]) < 1e-11 && fabs(result[1] - answer[1]) < 1e-11);
  free(result);
}

void test_x_squared_minus_one_hundred_millionth() {
  double* result = finding_roots_quadratic_equation(1, 0, -1e-8, 1e-7);
  double answer[1] = {0};
  assert(fabs(result[0] - answer[0]) < 1e-7);
  free(result);
}

int main() {
  // // Тест 1: a = 0
  test_linear_equation();


  // // Тест 2: a = 1, b = 0, c = -1
  test_x_squared_minus_one();

  // // Тест 3: a = 1, b = 0, c = 0
  test_x_squared();

  // // Тест 4: a = 1, b = 0, c = 1
  test_x_squared_plus_one();

  // Тест 5: a = 1, b = 0, c = -1E-7
  test_x_squared_minus_one_ten_millionth();

  // // Тест 6: a = 1, b = -1E+10, c = -1
  test_x_squared_minus_ten_billion_x_minus_one();

  // // Тест 7: a = 1, b = 0, c = -1E-8
  test_x_squared_minus_one_hundred_millionth();
}