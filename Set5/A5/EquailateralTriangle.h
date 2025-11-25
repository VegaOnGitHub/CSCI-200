#ifndef EQUAILATERAL_TRIANGLE_H
#define EQUAILATERAL_TRIANGLE_H

#include "Triangle.h"

class EquilateralTriangle : public Triangle {
public:
    bool validate() const override;
};

#endif  // EQUAILATERAL_TRIANGLE_H
