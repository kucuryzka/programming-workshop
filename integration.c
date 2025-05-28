#include "integration.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double integration(double a, double b, double (*func)(double), int h) {
  double start = fmin(a, b);
  double end = fmax(a, b);

  double step = (end - start) / h;
  double summ = 0.0;

  summ += (a + b) * 0.5;
  for (int i = 1; i < h; i++) {
    double next = start + i * step;
    summ += func(next);
  }

  if (a > b) {
    return -(summ * step);
  }
  return summ * step;
}
