#include "functions.h"
#include <math.h>

Roots find_roots(double a, double b, double c) {
    // присваиваем первоначальное значение корней: все пусто
    Roots roots;
    roots.count = 0;
    roots.roots = NULL;

    if (a == 0) {
        // невозможно вычислить корни при a = 0, все остается пустым
        roots.count = -1;
        return roots;
    }

    double d = b * b - 4 * a * c;
    if (d > 0) {
        // два вещественных корня
        roots.count = 2;
        roots.roots = malloc(2 * sizeof(double)); // выделение памяти для 2 значений double, т.е. для корней
        roots.roots[0] = (-b - sqrt(d)) / (2 * a);
        roots.roots[1] = (-b + sqrt(d)) / (2 * a);

        // сортировка корней
        if (roots.roots[0] > roots.roots[1]) {
            double temp = roots.roots[0];
            roots.roots[0] = roots.roots[1];
            roots.roots[1] = temp;
        }
    } else if (d == 0) {
        // один вещественный корень
        roots.count = 1;
        roots.roots = malloc(sizeof(double)); // выделение памяти для 1 значения double
        roots.roots[0] = -b / (2 * a);
    }
    return roots;
}

// освобождение памяти
void free_roots(Roots roots) {
    free(roots.roots);
}