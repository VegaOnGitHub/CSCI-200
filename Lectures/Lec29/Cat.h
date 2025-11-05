#ifndef CAT_H
#define CAT_H

#include "Animal.h"

class Cat : public Animal {
public:
    Cat();
    Cat(const Cat &OTHER);
    ~Cat();
    void speak() const override;
};

#endif//CAT_H