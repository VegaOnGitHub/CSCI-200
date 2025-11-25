#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Quadrilateral.h"

class Rhombus : public Quadrilateral {
public:
    bool validate() const override;
};

#endif  // RHOMBUS_H
