#include <stdio.h>
#include <stdlib.h>

// структура для хранения корней с самими корнями и их количеством
typedef struct {
    double* roots;
    int count;
} Roots;

// функция для нахождения корней квадратного уравнения
Roots find_roots(double a, double b, double c);

// функция для освобождения памяти
void free_roots(Roots roots);