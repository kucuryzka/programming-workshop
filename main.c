#include "integration.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

double quadratic(double num) {
  double res = num * num;
  return res;
}

double root(double num) {
  double res = sqrt(num);
  return res;
}

double log(double num) {
  double res = log2f(num);
  return res;
}

void test_equal_borders() {
  double result = integration(10, 10, quadratic, 1000);
  assert(result == 0);
}

void test_quadratic() {
  double result = integration(0.0, 5.0, quadratic, 10000000);
  assert(fabs(result - 125.0 / 3.0) < 1e-5);
}

void test_root() {
  double result = integration(0.0, 3.0, root, 10000000);
  assert(fabs(result - 2 * pow(3, 0.5)) < 1e-5);
}

void test_log() {
  double result = integration(0.0, 2.0, log, 10000000);
  assert(fabs(result - (2.0 - 2.0 / log(2))) < 1e-5);
}

void test_inverted_borders() {
  double result = integration(5.0, 0.0, quadratic, 10000000);
  assert(fabs(result + 125.0 / 3.0) < 1e-5);
}

int main(void) {
  test_equal_borders();

  test_quadratic();
  test_root();
  test_log();

  test_inverted_borders();
}