#include "Dog.h"
#include <iostream>
using namespace std;

Dog::Dog() {
    cout << "Creating a Dog" << endl;
    setName("Dog");
    // _name = "Dog";
    // _height = 1;
    // _weight = 1;
}

Dog::~Dog(){
    cout << "Destroying a Dog" << endl;
}

string Dog::bark() const {
    return "Dog:: Woof Woof!";
}

// string Dog::getName() const {
//     return _name;
// }

// void Dog::setName(const string& N) {
//     _name = N;
//     return;
// }