#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "Lion.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    Animal john;
    john.setName("John");
    cout << john.getName() << " is sleeping" << endl;
    cout << john.getName() << " is of type species " << john.getSpecies() << endl;
    john.sleep();
    john.speak();

    Dog odie;
    odie.setName("Odie");
    cout << odie.getName() << " is sleeping" << endl;
    cout << odie.getName() << " is of type species " << odie.getSpecies() << endl;
    odie.sleep();
    odie.speak();

    Cat garfield;
    garfield.setName("Garfield");
    cout << garfield.getName() << " is sleeping" << endl;
    garfield.sleep();
    garfield.speak();

    Lion simba;
    simba.setName("Simba");
    simba.pounce();
    simba.speak(); // using Lion speak - roar
    ((Cat)simba).speak(); // using Cat speak - meow
    simba.Cat::speak();
    simba.Animal::speak();

    vector<Animal*> menagerie(4);
    menagerie.at(0) = &john;
    menagerie.at(1) = &odie;
    menagerie.at(2) = &garfield;
    menagerie.at(3) = &simba;
    for(size_t i = 0; i < menagerie.size(); i++) {
        menagerie.at(i)->speak();

        // unsafe to cast since Lion::_numPounces does not exist on all objects we are pointing at
        // ( (Lion*) menagerie.at(i) )->pounce(); // uncomment to see broken behavior
    }

    Animal* pAnimal = new Lion;
    pAnimal->speak();
    delete pAnimal;
    
    return 0;
}