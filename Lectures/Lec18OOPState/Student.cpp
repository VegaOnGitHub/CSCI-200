#include "Student.h"

#include <iostream>

using namespace std;

Student::Student(){
    cwid = 11111;
    gpa = 4.0;
    name = "No Name";
}

 Student::Student(const int C, const double G, const std::string N){
    cwid = C;
    if (G < 0 || G > 4){
        gpa = 4.0;
    } else {
        gpa = G;
    }
    name = N;
}

void Student::printInfo(){
    cout << "CWID: " << cwid << " GPA: " << gpa << " Name: " << name << endl;
}

 double Student::getGPA() const{
    return gpa;
 }

void Student::setGPA(const double G){
    if (G < 0 || G > 4){
        gpa = 4.0;
    } else {
        gpa = G;
    }
}
