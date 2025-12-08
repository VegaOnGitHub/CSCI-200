#include "IsoscelesTriangle.h"

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

bool IsoscelesTriangle::validate() const {
    if (_vertices == nullptr || _numVertices != 3) {
        return false;
    }

    const double ab = distanceBetween(vertex(0), vertex(1));
    const double bc = distanceBetween(vertex(1), vertex(2));
    const double ca = distanceBetween(vertex(2), vertex(0));

    if (!formsTriangle(ab, bc, ca)) {
        return false;
    }

    return nearlyEqual(ab, bc) || nearlyEqual(bc, ca) || nearlyEqual(ca, ab);
}
