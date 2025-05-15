#include "quadratic_equation.h"
#include <assert.h>

void test_linear_equation() {
  int cnt_roots;
  double *result = finding_roots_quadratic_equation(0, 0, 0, 1e-9, &cnt_roots);
  assert(cnt_roots == 0);
  assert(result == NULL);
  free(result);
}

void test_x_squared_minus_one() {
  int cnt_roots;
  double *result =
      finding_roots_quadratic_equation(1, 0, -1, 1e-12, &cnt_roots);
  double answer[2] = {-1.0, 1.0};
  assert(cnt_roots == 2);
  assert(fabs(result[0] - answer[0]) < 1e-12 &&
         fabs(result[1] - answer[1]) < 1e-12);
  free(result);
}

void test_x_squared() {
  int cnt_roots;
  double *result = finding_roots_quadratic_equation(1, 0, 0, 1e-9, &cnt_roots);
  double answer[1] = {0};
  assert(cnt_roots == 1);
  assert(fabs(result[0] - answer[0]) < 1e-9);
  free(result);
}

void test_x_squared_plus_one() {
  int cnt_roots;
  double *result = finding_roots_quadratic_equation(1, 0, 1, 1e-9, &cnt_roots);
  assert(cnt_roots == 0);
  assert(result == NULL);
  free(result);
}

void test_x_squared_minus_one_ten_millionth() {
  int cnt_roots;
  double *result =
      finding_roots_quadratic_equation(1, 0, -1e-7, 1e-9, &cnt_roots);
  double answer[2] = {-3e-4, 3e-4};
  assert(cnt_roots == 2);
  assert(fabs(result[0] - answer[0]) < 1E-4 &&
         fabs(result[1] - answer[1]) < 1E-4);
  free(result);
}

void test_x_squared_minus_ten_billion_x_minus_one() {
  int cnt_roots;
  double *result =
      finding_roots_quadratic_equation(1, -1e+10, -1, 0, &cnt_roots);
  double answer[2] = {-1e-10, 1e+10};
  assert(cnt_roots == 2);
  assert(fabs(result[0] - answer[0]) < 1e-11 &&
         fabs(result[1] - answer[1]) < 1e-11);
  free(result);
}

void test_x_squared_minus_one_hundred_millionth() {
  int cnt_roots;
  double *result =
      finding_roots_quadratic_equation(1, 0, -1e-8, 1e-7, &cnt_roots);
  double answer[1] = {0};
  assert(cnt_roots == 1);
  assert(fabs(result[0] - answer[0]) < 1e-7);
  free(result);
}

int main() {
  test_linear_equation();
  test_x_squared_minus_one();
  test_x_squared();
  test_x_squared_plus_one();
  test_x_squared_minus_one_ten_millionth();
  test_x_squared_minus_ten_billion_x_minus_one();
  test_x_squared_minus_one_hundred_millionth();
}
