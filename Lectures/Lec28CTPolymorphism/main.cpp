#include "Dog.h"
#include "Cat.h"
#include <string>
#include <iostream>

using namespace std;

int main() {

    Animal john;
    john.setName("John");
    cout << john.getName();
    //  << " says "; 
    // cout << "..." << endl;
    John.speak();
    
    Dog odie;
    odie.setName("Odie");
    cout << odie.getName() << " says ";
    //odie.bark();
    odie.speak();

    Cat garfield;
    garfield.setName("Garfield");
    cout << garfield.getName() << " says ";
    garfield.meow();
    return 0;
}