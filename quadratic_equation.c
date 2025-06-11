#include <math.h>
#define NOT_A_QUADRATIC -1
#define ZERO_ROOTS 0
#define ONE_ROOT 1
#define TWO_ROOTS 2

int quadraticSolver(double a, double b, double c, double roots[2],
                    double epsilon) {
  if (fabs(a) < epsilon) {
    return NOT_A_QUADRATIC;
  }

  double discriminant = b * b - 4 * a * c;

  if (discriminant > epsilon) {
    if(a>0){
      roots[1] = ((-1) * b + sqrt(discriminant)) / (2 * a);
      if(fabs(b)<epsilon){
        roots[0] = -b/a - roots[1];
      }
      else{
        roots[0] = c/(a*roots[1]);
      }
      if (fabs(roots[0]) < epsilon) {
         roots[0] = 0;
      }
      if (fabs(roots[1]) < epsilon) {
         roots[0] = 0;
      }
    }
    else{
      roots[0] = ((-1) * b + sqrt(discriminant)) / (2 * a);
      if(fabs(b)<epsilon){
        roots[0] = -b/a - roots[1];
      }
      else{
        roots[0] = c/(a*roots[1]);
      }
      if (fabs(roots[0]) < epsilon) {
         roots[0] = 0;
      }
      if (fabs(roots[1]) < epsilon) {
         roots[0] = 0;
      }
    }

    if (fabs(roots[0] - roots[1]) < epsilon) {
      return ONE_ROOT;
    } else {
      return TWO_ROOTS;
    }
  } else if (discriminant < epsilon && discriminant >=0) {
    roots[0] = ((-1) * b) / (2 * a);
    if (fabs(roots[0]) < epsilon) {
      roots[0] = 0;
    }
    roots[1] = roots[0];
    return ONE_ROOT;
  } else {
    return ZERO_ROOTS;
  }
}
