#include "quadratic_equation.h"

double *finding_roots_quadratic_equation(double a, double b, double c,
                                         double eps, int *cnt_roots) {
  double *roots = NULL;
  *cnt_roots = 0;

  if (fabs(a) < eps) {
    return roots;
  }
  double discriminant = b * b - 4 * a * c;

  if (discriminant > eps) {
    *cnt_roots = 2;
    roots = malloc(2 * sizeof(double));
    roots[1] = (-b + sqrt(discriminant)) / (2 * a);
    roots[0] = c / (a * roots[1]);

    if (roots[1] < roots[0]) {
      double temp = roots[1];
      roots[1] = roots[0];
      roots[0] = temp;
    }

  } else if (discriminant < -eps) {
    return roots;
  } else {
    *cnt_roots = 1;
    roots = malloc(sizeof(double));
    roots[0] = -b / (2 * a);
  }
  return roots;
}
