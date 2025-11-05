#include "Cat.h"

#include <iostream>
using namespace std;

Cat::Cat() {
    cout << "Constructing Default Cat" << endl;
    mSpecies = "feline";
}

Cat::Cat(const Cat &OTHER) {
    cout << "Copy Constructing Cat" << endl;
    mSpecies = "feline";
    setName( OTHER.getName() );
}

Cat::~Cat() {
    cout << "Destroying Cat " << getName() << endl;
}

void Cat::speak() const {
    cout << "meow" << endl;
}