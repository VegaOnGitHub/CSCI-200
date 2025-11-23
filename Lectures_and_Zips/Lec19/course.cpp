#include "course.h"
#include <iostream>
#include <string>


using namespace std;

Course::Course(){
    _title = "CSM101";
    _enrollment = 0;
}

Course::Course(const string TITLE){
    _title = TITLE;
}

string getTitle()