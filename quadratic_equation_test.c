#include <assert.h>
#include <math.h>

#include "quadratic_equation.h"
#define NOT_A_QUADRATIC -1
#define ZERO_ROOTS 0
#define ONE_ROOT 1
#define TWO_ROOTS 2

void test1() {
  double a = 0;
  double b = 0;
  double c = 0;
  double roots[2];
  double epsilon = 1e-7;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(NOT_A_QUADRATIC == countOfRoots);
}

void test2() {
  double a = 1;
  double b = 0;
  double c = -1;
  double roots[2];
  double epsilon = 1e-7;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(TWO_ROOTS == countOfRoots);
  assert(-1.0 == roots[0]);
  assert(1.0 == roots[1]);
}

void test3() {
  double a = 1;
  double b = 0;
  double c = 0;
  double roots[2];
  double epsilon = 1e-7;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(ONE_ROOT == countOfRoots);
  assert(fabs(roots[0])<epsilon);
}

void test4() {
  double a = 1;
  double b = 0;
  double c = 1;
  double roots[2];
  double epsilon = 1e-7;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(ZERO_ROOTS == countOfRoots);
}

void test5() {
  double a = 1;
  double b = 0;
  double c = -1e-7;
  double roots[2];
  double epsilon = 1e-7;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(TWO_ROOTS == countOfRoots);
  assert(-3e-4 == round(roots[0] * 10000) / 10000);
  assert(3e-4 == round(roots[1] * 10000) / 10000);
}

void test6() {
  double a = 1;
  double b = -1e10;
  double c = -1;
  double roots[2];
  double epsilon = 1e-11;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(TWO_ROOTS == countOfRoots);
  assert(-1e-10 == roots[0]);
  assert(1e10 == roots[1]);
}

void test7() {
  double a = 1;
  double b = 0;
  double c = -1e-8;
  double roots[2];
  double epsilon = 1e-7;
  int countOfRoots = quadraticSolver(a, b, c, roots, epsilon);
  assert(ONE_ROOT == countOfRoots);
  assert(0 == roots[0]);
  }

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  return 0;
}
