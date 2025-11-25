#ifndef ISOSCELES_TRIANGLE_H
#define ISOSCELES_TRIANGLE_H

#include "Triangle.h"

class IsoscelesTriangle : public Triangle {
public:
    bool validate() const override;
};

#endif  // ISOSCELES_TRIANGLE_H
