#include "Lion.h"

#include <iostream>
using namespace std;


Lion::Lion() {
    cout << "Constructing Default Lion" << endl;
    mSpecies = "leone";
    _numPounces = 3;
}

Lion::~Lion() {
    cout << "Destroying Lion " << getName() << endl;
}

void Lion::speak() const {
    cout << "ROAAARRRR" << endl;
}

void Lion::pounce() const {
    for(int i = 0; i < _numPounces; i++) {
        cout << "attack!" << endl;
    }
}