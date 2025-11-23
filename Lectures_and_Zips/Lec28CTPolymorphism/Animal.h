#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal {
    public:
        Animal();
        ~Animal();

        std::string getName() const;
        void setName(const std::string& N);

        virtual void speak() const;

    private:
        std::string _name;
        double _height;
        double _weight;

};

#endif