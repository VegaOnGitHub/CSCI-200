#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal {
public:
    Animal();
    virtual ~Animal();
    std::string getName() const;
    void setName(std::string NAME);
    std::string getSpecies() const;
    void sleep() const;
    virtual void speak() const;
protected:
    std::string mSpecies;
private:
    std::string _name;
};

#endif//ANIMAL_H