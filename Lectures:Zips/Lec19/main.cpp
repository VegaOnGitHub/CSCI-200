#include "course.h"
#include <cstddef>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>

using namespace std;

int main(){

    std::vector<string> courses;
    courses[0] = "CSCI";
    courses[1] = "ENDS";
    courses[2] = "MATH";
    courses[3] = "HASS";

    for (size_t i = 0; i < courses.size(); i++){
        cout << "courses avalible " << courses[i] << endl;
        
    }

    return 0;
}