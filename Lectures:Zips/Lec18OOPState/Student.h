#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student{
    private: 
        int cwid;
        double gpa;
        std::string name;
        
    public: //access control
        
        Student(); // default constructor
        Student(const int C, const double G, const std::string N); // parameterized constructor
        void printInfo();
        double getGPA() const;
        void setGPA(const double G);
};

#endif // STUDENT_H