#include "Dog.h"

#include <iostream>
using namespace std;

Dog::Dog() {
    cout << "Constructing Default Dog" << endl;
    mSpecies = "canine";
}

Dog::~Dog() {
    cout << "Destroying Dog " << getName() << endl;
}

void Dog::speak() const {
    cout << "WOOF!" << endl;
}