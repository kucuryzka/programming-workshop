#include "functions.h"

double* finding_roots_quadratic_equation(double a, double b, double c, double eps) {
    // корней нет изначально
    double* roots = NULL;

    if (fabs(a) < eps) {
        return roots;
    }
    printf("%.10f\n%.10f\n%.10f\n%.10f\n", a, b, c, eps);
    double d = b * b - 4 * a * c;
    printf("Дискриминант: %.21f\n", d);

    if (d > eps) { // Дискриминант больше нуля
        roots = malloc(2 * sizeof(double));
        roots[0] = (-b - sqrt(d)) / (2 * a);
        roots[1] = (-b + sqrt(d)) / (2 * a);

        // Сортировка корней по возрастанию
        if (roots[0] > roots[1]) {
            double temp = roots[0];
            roots[0] = roots[1];
            roots[1] = temp;
        }
    } else if (d < -eps) { // Дискриминант меньше нуля
        return roots;
    } else { // Дискриминант равен нулю
        roots = malloc(sizeof(double));
        roots[0] = -b / (2 * a);
    }
    return roots;
}