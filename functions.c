#include <math.h>
#include "functions.h"

double func1(int a, int b, double(*func) (double))
{
    double summ = 0.0;
    for (int i = a; i < b; i++)
    {
        double num = i;
        summ += ((func(num) + func(num + 1.0)) / 2);
    
    }
    

    return summ;
}


double quadratic(double num)
{   
    double res = num * num;
    return res;
}


double root(double num)
{
    double res = sqrt(num);
    return res;
}


double log(double num)
{
    double res = 2;
    return res;
}