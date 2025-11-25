#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Polygon.h"

class Triangle : public Polygon {
public:
    Triangle();
    ~Triangle() override = default;
};

#endif  // TRIANGLE_H
