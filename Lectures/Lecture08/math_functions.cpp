#include "math_functions.h"
#include <iomanip>
#include <iostream>


using namespace std;


double add(const double LHS, const double RHS) {
    return LHS + RHS;
}

double sub(const double LHS, const double RHS) {
    return LHS - RHS;
}

double mult(const double LHS, const double RHS) {
    return LHS * RHS;
}

double div(const double LHS, const double RHS) {
    return LHS / RHS;
}


double mod(const double LHS, const double RHS) {
    double quotient = div(LHS, RHS);
    double balance = quotient - (int)quotient;
    return mult(balance, RHS);
}


void print_equation(const double LHS, const char OP, const double RHS, const double RESULT) {
    cout << setw(10) << LHS << " " 
         << OP << " " 
         << setw(10) << RHS << " = " 
         << setw(10) << RESULT << endl;
}