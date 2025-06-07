#include "quadratic.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_zero_a() {
    double a = 0;
    double b = 1;
    double c = 1;
    double epsilon = 1e-9;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(0 == root_count);
}

void test_two_real_roots() {
    double a = 1;
    double b = 0;
    double c = -1;
    double epsilon = 1e-9;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(2 == root_count);
    assert(fabs(-1 - roots[0]) < epsilon);
    assert(fabs(1 - roots[1]) < epsilon);
}

void test_one_real_root() {
    double a = 1;
    double b = 0;
    double c = 0;
    double epsilon = 1e-9;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(1 == root_count);
    assert(fabs(0 - roots[0]) < epsilon);
}

void test_no_real_roots() {
    double a = 1;
    double b = 0;
    double c = 1;
    double epsilon = 1e-9;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(0 == root_count);
}

void test_small_c_positive_discriminant() {
    double a = 1;
    double b = 0;
    double c = -1E-7;
    double epsilon = 1e-9;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(2 == root_count);
    assert(fabs(-3E-4 - roots[0]) < 1e-4);
    assert(fabs(3E-4 - roots[1]) < 1e-4);
}

void test_large_b_positive_discriminant() {
    double a = 1;
    double b = -1E+10;
    double c = -1;
    double epsilon = 1e-11;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(2 == root_count);
    assert(fabs(-1E-10 - roots[0]) < epsilon);
    assert(fabs(1E+10 - roots[1]) < epsilon);
}

void test_very_small_c_positive_discriminant() {
    double a = 1;
    double b = 0;
    double c = -1e-8;
    double epsilon = 1e-9;
    double roots[2];
    int root_count;

    find_roots(a, b, c, roots, &root_count, epsilon);

    assert(2 == root_count);
    assert(fabs(-sqrt(1e-8) - roots[0]) < epsilon);
    assert(fabs(sqrt(1e-8) - roots[1]) < epsilon);
}

int main() {
    test_zero_a();
    test_two_real_roots();
    test_one_real_root();
    test_no_real_roots();
    test_small_c_positive_discriminant();
    test_large_b_positive_discriminant();
    test_very_small_c_positive_discriminant();

    printf("All tests passed!\n");
    return 0;
}
