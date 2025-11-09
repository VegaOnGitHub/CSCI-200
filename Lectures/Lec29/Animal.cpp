#include "Animal.h"

#include <iostream>
using namespace std;

Animal::Animal() {
    cout << "Constructing Default Animal" << endl;
    _name = "Animal";
    mSpecies = "animalia";
}

Animal::~Animal() {
    cout << "Destroying Animal " << _name << endl;
}

string Animal::getName() const { 
    return _name; 
}

void Animal::setName(const string NAME) { 
    cout << "Setting name " << NAME << endl;
    _name = NAME; 
}

string Animal::getSpecies() const { 
    return mSpecies; 
}

void Animal::sleep() const { 
    cout << "zzz" << endl; 
}

// void Animal::speak() const { 
//     cout << "..." << endl; 
// }
