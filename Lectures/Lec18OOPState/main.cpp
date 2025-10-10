#include "Student.h"

#include <iostream>

using namespace std;

int main(){
    Student ana = Student();
    // ana.cwid = 1;
    // ana.gpa = 3.9;
    // cout << "Enter a name: ";
    // cin >> ana.name;
    // ana.printInfo();

    Student bob; //implicity calling default constructor
    bob.printInfo();

    Student carie = Student(33333, 4.9, "Carie"); // explicitly calling parameterized constructor
    carie.printInfo();
    // carie.gpa = 4.5;
    // carie.printInfo();



    return 0;
}