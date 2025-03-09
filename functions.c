#include "functions.h"
#include <math.h>
#include <stdio.h>

double func1(int a, int b, double (*func)(double), double h) {
  double step = (b - a) / h;
  double summ = 0.0;
  for (double i = a; i < b; i += step) {
    double num = i;
    summ += ((func(num) + func(num + step)) / 2) * step;
  }

  return summ;
}

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
