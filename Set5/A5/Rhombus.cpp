#include "Rhombus.h"

#include <cmath>

namespace {
constexpr double kEpsilon = 1e-6;

bool nearlyEqual(double lhs, double rhs) {
    return std::fabs(lhs - rhs) <= kEpsilon;
}

bool formsTriangle(double a, double b, double c) {
    return a > kEpsilon && b > kEpsilon && c > kEpsilon && a + b > c + kEpsilon &&
           a + c > b + kEpsilon && b + c > a + kEpsilon;
}
}  // namespace

bool Rhombus::validate() const {
    if (_vertices == nullptr || _numVertices != 4) {
        return false;
    }

    const double s01 = distanceBetween(vertex(0), vertex(1));
    const double s12 = distanceBetween(vertex(1), vertex(2));
    const double s23 = distanceBetween(vertex(2), vertex(3));
    const double s30 = distanceBetween(vertex(3), vertex(0));
    const double diag02 = distanceBetween(vertex(0), vertex(2));

    if (!formsTriangle(s01, s12, diag02) || !formsTriangle(diag02, s23, s30)) {
        return false;
    }

    return nearlyEqual(s01, s12) && nearlyEqual(s12, s23) && nearlyEqual(s23, s30);
}
