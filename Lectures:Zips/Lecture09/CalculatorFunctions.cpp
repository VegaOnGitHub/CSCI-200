// include the prototypes to ensure definition header matches declaration header
#include "CalculatorFunctions.h"

// every file must include any other libraries it depends on
#include <iomanip>
#include <iostream>
using namespace std;

// separate function definitions

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
    const double QUOTIENT = div(LHS, RHS);
    const double BALANCE = QUOTIENT - (int)QUOTIENT;
    return mult(BALANCE, RHS);
}

void print_equation(const double LHS, const char OP, const double RHS, const double RESULT) {
    cout << setw(10) << LHS    << " " 
         << setw(5)  << OP     << " " 
         << setw(10) << RHS    << " = " 
         << setw(10) << RESULT << endl;
}
