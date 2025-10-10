#ifndef COURSE_H
#define COURSE_H

#include <string>

using namespace std;

class Course{
    public:
        Course();
        Course(const string TITLE);
        std::string getTitle();
        int getEnrollment();
        void registerStduent();
        void withdrawStudent();

    private:
        int _enrollment;
        string _title;


};

#endif