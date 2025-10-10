/* CSCI 200: Fix Loop and Function Errors
 *
 * Author: Daniel Vega
 *
 * Description:
 *    This program illustrates a variety of common loop and function 
 *    errors.  Fix the errors in each section.
 * 
 * Copyright 2025 Dr. Jeffrey Paone
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

#include <iostream>     // for cout, cin, endl etc.
#include <random>       // for mt19937 generator
using namespace std;

/**
 * @brief justs prints a smiley face.
 * 
 */
// FIX: Function didn't exist previously
void printSmileyFace(){
    cout << ":)" << endl;
}

/**
 * @brief adds five to the given parameter
 * @param x integer to be added to
 * @returns parameter plus five
 */
// FIX: Passed by reference
void add_five( int &x ) {
     x += 5;
}

/**
 * @brief generates a single random integer number within the expected range
 * @param MIN lower inclusive bound of range
 * @param MAX upper inclusive bound of range
 * @returns random integer within the range [MIN, MAX]
 */
int generate_random_integer(const int MIN, const int MAX) {
    // create the Mersenne Twister generator
    // FIX: Correctly constructed uniform_int_distribution with MIN and MAX.
    // TESTS: For min=1, max=1 -> always prints 1. For range 1–10 -> numbers fall in [1,10].
    random_device rd;
    mt19937 mt( rd() );
    uniform_int_distribution<int> dist(MIN, MAX);

    return dist(mt);
}

/**
 * @brief generates a single random floating point number within the expected range
 * @param MIN lower inclusive bound of range
 * @param MAX upper inclusive bound of range
 * @return random float within the range [MIN, MAX]
 */
float generate_random_float(const float MIN, const float MAX) {
    // create the Mersenne Twister generator
    // FIX: Correct construction with MIN and MAX.
    // TESTS: For min=1.0, max=1.0 -> always prints 1.0. For range 0.0–1.0 -> numbers fall in [0.0,1.0).
    random_device rd;
    mt19937 mt( rd() );
    uniform_real_distribution<float> dist(MIN, MAX);

    return dist(mt);
}

/**
 * @brief sums three integer values
 * @param x first value to be added
 * @param y second value to be added
 * @param z third value to be added
 * @returns the sum of all three parameters
 */
int sum( int x, int y, int z ) {
    // FIX: Changed return expression to x+y+z (original was x+x+x).
    // TESTS: Input (1,2,3) -> prints 6. Input (5,0,-2) -> prints 3.
    return x + y + z;
}

/**
 * @brief multiples two floats together
 * @param a first value to multiply
 * @param b second value to multipl
 * @returns the product of the two float parameters
 */
float multiply( float a, float b) {
    // FIX: Removed bad syntax, added proper multiplication and return. Removed stray semicolon after function.
    // TESTS: Input (2.0,3.0) -> prints 6. Input (-1.5,4.0) -> prints -6.   
    float C = a * b;
    return C;
} // <-- no stray semicolon here

/**
 * @brief runs test summing numbers in the range [1, N]
 */
void loop_test_1() {
    // FIX: Changed loop condition from i<n to i<=n.
    // TESTS: Input n=5 -> sum=15 (1+2+3+4+5). Input n=1 -> sum=1.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 1 " << endl;
    cout << "******************" << endl;

    int n;  
    cout << "Enter a number greater than 1 to sum up to: ";
    cin >> n;

    int sum = 0;
    for( int i = 1; i <= n; ++i ) {
         sum += i;
     }
    cout << "The sum of the numbers from 1 to " << n << " (inclusive) is: " << sum << endl;
}

/**
 * @brief runs test summing set of prices entered by the user
 */
void loop_test_2() {
    // FIX: Moved totalPrice initialization before loop (was inside). Used double for money.
    // TESTS: Items = 3, prices 1.50, 2.50, 3.00 -> total = 7.00. Items = 0 -> total = 0.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 2 " << endl;
    cout << "******************" << endl;

    int numItems;
    cout << "How many items do you have? ";
    cin >> numItems;
    cout << endl;

    int counter = 1;
    double totalPrice = 0.0, price = 0.0;
    while (counter <= numItems) {
        cout << "Enter the price of item " << counter << ": ";
        cin >> price;
        totalPrice += price;
        counter++;
    }
    cout << "The total price is: " << totalPrice << endl;
}

/**
 * @brief runs test summing numbers in the range [1, N]
 */
void loop_test_3() {
    // FIX: Incremented counter inside loop and corrected condition to while(counter <= n).
    // TESTS: Input n=3 -> Final sum = 6.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 3 " << endl;
    cout << "******************" << endl;

    int n;
    cout << "What number do you wish me to sum to?" << endl;
    cin >> n;

    int sum = 0, counter = 1;
    do {
        sum += 1;
        cout << "Sum so far: " << sum << endl;
        counter++;
    } while (counter <= n); 

    cout << endl << "Section III Recap" << endl;

    cout << "I calculated the sum of numbers from 1 to " << n << " (inclusive) as " << sum << endl;
}

/**
 * @brief runs test summing i^2 in the range [1, N]
 */
void loop_test_4() {
    // FIX: Kept loop counting down from n to 1.
    // TESTS: Input n = 3 -> result 1^2+2^2+3^2=14. Input n = 1 -> result = 1.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 4 " << endl;
    cout << "******************" << endl;

    cout << "I will now calculate the sum of squares from 1 to N (inclusive)" << endl;
    
    int n;
    cout << "Enter N: ";
    cin >> n;

    int sum = 0;
    for( int i = 0; i <= n; ++i ) {
        sum += i*i;
    }

    cout << "The sum of squares from 1 to " << n << " is: " << sum << endl;
}

/**
 * @brief runs test summing i^3 in the range [1, N]
 */
void loop_test_5() {
    // FIX: Changed condition to while(counter <= n) and moved counter++ inside loop. Removed hardcoded 10.
    // TESTS: Input n = 3 -> result 1^3+2^3+3^3=36. Input n = 1 -> result = 1.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 5 " << endl;
    cout << "******************" << endl;

    cout << "I will now calculate the sum of cubes from 1 to N (inclusive)" << endl;

    int n;
    cout << "Enter N: ";
    cin >> n;

    int sum = 0, counter = 1;
    while( counter <= n ) {
        sum += (counter * counter * counter);
        counter++;
    }

    cout << "The sum of cubes from 1 to " << n << " is: " << sum << endl;
}

/**
 * @brief runs test using function to add five to an entered value
 */
void function_test_1() {
    // FIX: Removed assignment from add_five() since it returns void, not int.
    // TESTS: Input 10 trees -> output 15 trees.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 1" << endl;
    cout << "******************" << endl;

    int numTrees;
    cout << "How many trees do you currently have? ";
    cin >> numTrees;
    cout << "There are initially " << numTrees << " trees." << endl;
    add_five( numTrees );
    cout << "We planted five trees, there are now " << numTrees << " trees." << endl;
}

/**
 * @brief runs test to call a function that outputs a smiley face to the standard out
 * 
 */
void function_test_2() {
    // FIX: Added missing printSmileyFace() function.
    // TESTS: Prints “:)” when run.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 2" << endl;
    cout << "******************" << endl;

    printSmileyFace();
}

/**
 * @brief runs test to generate five random integers within a provided range
 */
void function_test_3() {
    // FIX: No changes required.
    // TESTS: Enter min = 1, max=1 -> prints five 1s. Enter min = 5, max = 7 -> numbers fall in [5,7].

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 3" << endl;
    cout << "******************" << endl;

    int min, max;
    cout << "Enter the minimum integer range value: ";
    cin >> min;
    cout << "Enter the maximum integer range value: ";
    cin >> max;

    cout << "Five different random numbers are: " << endl;
    for( int i = 0; i < 5; i++ ) {
        cout << "\t" << generate_random_integer(min, max) << endl;
    }
}

/**
 * @brief runs test to use function to sum three values
 */
void function_test_4() {
    // FIX: Added missing third argument when calling sum().
    // TESTS: Input (1,2,3) -> result 6. Input (10,20,30) -> result 60.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 4" << endl;
    cout << "******************" << endl;

    int num1, num2, num3;
    cout << "Enter three integer numbers: ";
    cin >> num1 >> num2 >> num3;
    cout << "The sum of all three is " << sum( num1, num2, num3 ) << endl;
}

/**
 * @brief runs test to generate five random floats within a provided range
 */
void function_test_5() {
    // FIX: Corrected call to generate_random_float(min, max) with arguments.
    // TESTS: Enter min = 0.0, max = 1.0 -> prints 5 floats all in [0.0,1.0).

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 5" << endl;
    cout << "******************" << endl;

    float min, max;
    cout << "Enter the minimum float range value: ";
    cin >> min;
    cout << "Enter the maximum float range value: ";
    cin >> max;
    cout << "Five different random floats are: " << endl;
    for( int i = 0; i < 5; ++i ) {
        cout << "\t" << generate_random_float(min, max) << endl;
    }
}

/**
 * @brief runs test to use function to multiply two provided numbers
 */
void function_test_6() {
    // FIX: Fixed multiply() implementation so call works.
    // TESTS: Input (2.5,4.0) -> result 10. Input (-2,3) -> result -6.

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 6" << endl;
    cout << "******************" << endl;

    float leftHandSide, rightHandSide;
    cout << "Enter two floats: ";
    cin >> leftHandSide >> rightHandSide;
    cout << "Their product is: " << multiply( leftHandSide, rightHandSide ) << endl;
}

int main() {
    cout << "Welcome To Looping Function World!" << endl;
    
    loop_test_1();        // run looping test 1
    loop_test_2();        // run looping test 2
    loop_test_3();        // run looping test 3
    loop_test_4();        // run looping test 4
    loop_test_5();        // run looping test 5

    function_test_1();    // run function test 1
    function_test_2();    // run function test 2
    function_test_3();    // run function test 3
    function_test_4();    // run function test 4
    function_test_5();    // run function test 5
    function_test_6();    // run function test 6

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Done" << endl;
    cout << "******************" << endl;

    cout << endl << "Congrats!  You fixed them all (hopefully correctly!)" << endl << endl << "Goodbye" << endl << endl;

    return 0;
}