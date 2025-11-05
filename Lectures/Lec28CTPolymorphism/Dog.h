#ifndef DOG_H
#define DOG_H

#include "Animal.h"
#include <string> 

class Dog : public Animal {
    public:
        Dog();
        ~Dog();
        
        // void bark() const;

        void speak() const override;

    private:
        
};
#endif