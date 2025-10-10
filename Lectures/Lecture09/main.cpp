/* 
 * CSCI 200: Lecture 09 Function and Multiple Files Example
 *
 * Author: Dr. Jeffrey Paone
 *
 *    Starter code used to work through separate function 
 *    declaration & definition
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

// include system library files with < >
#include <iomanip>
#include <iostream>
using namespace std;

// include local files with quotes
// always only include header files!  if we were to include the cpp files, since each
// cpp gets compiled then at linking time we would get redefinition errors due to 
// the function implementations existing twice.  the compiler ensures each file is
// written correctly while the linker ensures the project is set up correctly
#include "CalculatorFunctions.h"

/**
 * @brief runs our program!
 * @return int result code signalling how our program exited
 */
int main() {
    cout << "Welcome to the Fancy Five Function Calculator!" << endl;
    
    // prompt the user to enter two numeric values for our calculator
    double firstValue, secondValue;
    cout << "Enter two double values: ";
    cin >> firstValue >> secondValue;

    cout << endl << "The results are...::drum roll::..." << endl << endl;

    // run each equation and display result
    cout << fixed << setprecision(3) << right;
    // mouse over the function names to see the documentation tooltip!
    print_equation(firstValue, '+', secondValue, add(firstValue, secondValue));
    print_equation(firstValue, '-', secondValue, sub(firstValue, secondValue));
    print_equation(firstValue, '*', secondValue, mult(firstValue, secondValue));
    print_equation(firstValue, '/', secondValue, div(firstValue, secondValue));
    print_equation(firstValue, '%', secondValue, mod(firstValue, secondValue));

    cout << endl << "Run this program again to do some more math!" << endl;
    return 0;
}