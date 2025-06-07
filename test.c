#include "quadratic.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void root_test_1() {
  double a = 0;
  double b = 1;
  double c = 1;
  double e = 0;
  double roots[2];
  int root_count;

  find_roots(a, b, c, roots, &root_count, e);

  assert(0 == root_count);
}

void root_test_2() {
  double a = 1;
  double b = 0;
  double c = -1;
  double e = 0;
  double roots[2];
  int root_count;
  find_roots(a, b, c, roots, &root_count, 0);

  assert(2 == root_count);
  assert(-1 == roots[0]);
  assert(1 == roots[1]);
}
void root_test_3() {
  double a = 1;
  double b = 0;
  double c = 0;
  double e = 0;
  double roots[2];
  int root_count;

  find_roots(a, b, c, roots, &root_count, e);

  assert(1 == root_count);
  assert(roots[0] == 0);
}
void root_test_4() {
  double a = 1;
  double b = 0;
  double c = 1;
  double e = 0;
  double roots[2];
  int root_count;

  find_roots(a, b, c, roots, &root_count, e);

  assert(0 == root_count);
}
void root_test_5() {
  double a = 1;
  double b = 0;
  double c = -1E-7;
  double roots[2];
  int root_count;
  double epsilon = 1e-8;

  find_roots(a, b, c, roots, &root_count, epsilon);

  assert(2 == root_count);
  assert(fabs(-3E-4 - roots[0]) < 0.0001);
  assert(fabs(3E-4 - roots[1]) < 0.0001);
}
void root_test_6() {
  double a = 1;
  double b = -1E+10;
  double c = -1;
  double roots[2];
  int root_count;
  double epsilon = 1e-11;

  find_roots(a, b, c, roots, &root_count, epsilon);

  assert(2 == root_count);

  assert(fabs(-1E-10 - roots[0]) < epsilon);
  assert(fabs(1E+10 - roots[1]) < epsilon);
}
void root_test_7() {
  double a = 1;
  double b = 0;
  double c = -1e-8;
  double epsilon = 1e-7;
  double roots[2];
  int root_count;

  find_roots(a, b, c, roots, &root_count, epsilon);
  assert(1 == root_count);
  assert(fabs(0 - roots[0]) < epsilon);
}
int main() {
  root_test_1();
  root_test_2();
  root_test_3();
  root_test_4();
  root_test_5();
  root_test_6();
  root_test_7();

  return 0;
}
