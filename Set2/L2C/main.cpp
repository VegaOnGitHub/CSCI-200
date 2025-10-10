/* CSCI 200: L2C
 *
 * Author: Daniel Vega
 *
 * Programs asks user whether they wish to convert from polar coordinates to cartesian coordinates or vice versa
 * that's kinda it. Also all functions prototypes are in an H file and definitions in their own .cpp file as instructed.
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include "coordinate_conversion.h" //functions for converting between polar and cartesian coordinates

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/

  int choice;
    cout << "1: (r, theta) -> (x, y)\n2: (x, y) -> (r, theta)\n";
    cin >> choice;
    if (choice == 1) {
        double r, theta, x, y;

        cout << "Enter r and theta: ";
        cin >> r >> theta;

        polar_to_cartesian(r, theta, &x, &y);

        cout << "(" << r << ", " << theta << ") -> (" << x << ", " << y << ")\n";

    } else if (choice == 2) {
        double x, y, r, theta;

        cout << "Enter x and y: ";
        cin >> x >> y;

        cartesian_to_polar(x, y, &r, &theta);

        cout << "(" << x << ", " << y << ") -> (" << r << ", " << theta << ")\n";

    }



  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}