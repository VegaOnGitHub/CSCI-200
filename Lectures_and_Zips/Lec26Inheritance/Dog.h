#ifndef DOG_H
#define DOG_H
#include "animal.h"

#include <string> 

class Dog : public Animal{
    public:
        Dog();
        ~Dog();
        // std::string getName() const;
        // void setName(const std::string& N);
        std::string bark() const;

    private:
        // std::string _name;
        // double _height;
        // double _weight;
};
#endif