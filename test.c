#include "functions.h"
#include <stdio.h>

int main(void) {
  int a, b;
  double (*func)(double) = log;
  printf("enter the beginning and the end of the segment:\n");
  scanf("%i", &a);
  scanf("%i", &b);

  printf("definite integral equals for interval from %i to %i:\n", a, b);
  printf("for log: %f\n", func1(a, b, func, 100));

  func = quadratic;
  printf("for quadratic: %f\n", func1(a, b, func, 100));

  func = root;
  printf("for root: %f\n", func1(a, b, func, 100));

  return 0;
};
