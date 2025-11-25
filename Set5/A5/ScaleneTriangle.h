#ifndef SCALENE_TRIANGLE_H
#define SCALENE_TRIANGLE_H

#include "Triangle.h"

class ScaleneTriangle : public Triangle {
public:
    bool validate() const override;
};

#endif  // SCALENE_TRIANGLE_H
