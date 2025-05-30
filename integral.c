#include "integralFunc.h"
double calculation(double a, double b, int n, double (*func)(double)) {
  double h = (b - a) / n; // длина одного разбиения
  double sum = 1 / 2 * (func(a) + func(b));
  for (int i = 1; i < n; i++) {
    double x = a + i * h;
    sum += func(x);
  }
  return h * sum;
}
