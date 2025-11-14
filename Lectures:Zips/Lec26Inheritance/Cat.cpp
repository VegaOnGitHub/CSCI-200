#include "Cat.h"
#include <iostream>
using namespace std;

Cat::Cat() {
    cout << "Creating a Cat" << endl;
    _name = "Cat";
    _height = 1;
    _weight = 1;
}

Cat::~Cat(){
    cout << "Destroying a Cat" << endl;
}

string Cat::getName() const {
    return _name;
}

void Cat::setName(const string& N) {
    _name = N;
    return;
}
        
string Cat::meow() const {
    return "Cat:: Meow Meow!";
}