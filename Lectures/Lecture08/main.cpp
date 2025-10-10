/* CSCI 200: Lecture 08 Function Examples
 *
 * Author: Dr. Jeffrey Paone
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Class!
 *
 * Starter code used to work through separate function declaration & definition
 */

#include <iomanip>
#include <iostream>
#include "math_functions.h"

using namespace std;

int main() {
    cout << "Welcome to the Fancy Five Function Calculator!" << endl;
    
    // prompt the user to enter two numeric values for our calculator
    double firstValue, secondValue;
    cout << "Enter two double values: ";
    cin >> firstValue >> secondValue;

    cout << endl << "The results are...::drum roll::..." << endl << endl;

    // run each equation and display result
    cout << fixed << setprecision(3) << right;
    print_equation(firstValue, '+', secondValue, add(firstValue, secondValue));
    print_equation(firstValue, '-', secondValue, sub(firstValue, secondValue));
    print_equation(firstValue, '*', secondValue, mult(firstValue, secondValue));
    print_equation(firstValue, '/', secondValue, div(firstValue, secondValue));
    print_equation(firstValue, '%', secondValue, mod(firstValue, secondValue));

    cout << endl << "Run this program again to do some more math!" << endl;
    return 0;
}

