#ifndef LION_H
#define LION_H

#include "Cat.h"

class Lion : public Cat {
public:
    Lion();
    ~Lion();
    void speak() const override;
    void pounce() const;
private:
    int _numPounces;
};

#endif//LION_H