#include <math.h>
#include <stdio.h>

static void sort_roots(double *root1, double *root2) {
    if (*root1 > *root2) {
        double temp = *root1;
        *root1 = *root2;
        *root2 = temp;
    }
}

void find_roots(double a, double b, double c, double *roots, int *root_count,
                double epsilon) {
    if (fabs(a) <= epsilon) {
        *root_count = 0;
        return;
    }

    double discriminant = (b * b) - 4 * a * c;
    if (fabs(discriminant) <= epsilon) {
        discriminant = 0;
    }

    if (discriminant > epsilon) {
        roots[0] = (-b + sqrt(discriminant)) / (2 * a);
        roots[1] = (-b - sqrt(discriminant)) / (2 * a);
        sort_roots(&roots[0], &roots[1]);
        *root_count = 2;
    } else if (fabs(discriminant) <= epsilon) {
        roots[0] = -b / (2 * a);
        *root_count = 1;
    } else {
        *root_count = 0;
    }
}
