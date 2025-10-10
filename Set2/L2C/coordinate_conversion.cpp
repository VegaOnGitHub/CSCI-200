#include <cmath>
#include "coordinate_conversion.h"
using namespace std;

void polar_to_cartesian(const double r, const double theta, double* x, double* y) {
    *x = r * cos(theta);
    *y = r * sin(theta);
}

void cartesian_to_polar(const double x, const double y, double* r, double* theta) {
    *r = sqrt(x * x + y * y);
    *theta = atan2(y, x);
}