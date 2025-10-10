/* CSCI 200: Lab 1B 
 *
 * Author: Daniel Vega
 *
 * Description: This program asks the user for a mininum and maximum values to generate randomly, the number that is generated
 * will then be classified into quartiles. It will also ask the user if it would like to generate another number
 * within the range of values they orginally gave.
 *
 */



// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <random> // for mt19937, random_device, and uniform_real_distribution (had to look up how to use since uniform_int_distribution doesn't work with doubles)

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

double randomValueGeneration(double min, double max){

    random_device rd;
    mt19937 mt(rd());

    uniform_real_distribution<double> dist(min, max);
    double rv = dist(mt);

    cout << "The Random Value is: " << rv << endl;
    return rv;
}
void quartileClassification(double rv, double max) {
    if (rv <= max/4) {
        cout << "Your Value falls within the first quartile" << endl;
    } else if (rv <= max/2) {
        cout << "Your Value falls within the second quartile" << endl;
    } else if (rv <= 3*max/4) {
        cout << "Your Value falls within the third quartile" << endl;
    } else if (rv <= max) {
        cout << "Your Value falls within the fourth quartile" << endl;
    } else {
        cout << "Value exceeds maximum" << endl;
    }
}
// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/

    double maximum, mininum, rv, diff1, diff2;
    char answer;

    cout << "Enter a Minimum Value: ";
    cin >> mininum;
    cout << "Enter a Maximum Value: ";
    cin >> maximum;

    diff1 = maximum - mininum;

    rv = randomValueGeneration(mininum, maximum);
    
    diff2 = rv - mininum;

    quartileClassification(diff2, diff1);

    answer = 'y';

    while (answer == 'y' || answer == 'Y'){

        cout << "Do you want another random value? (Y/N)" << endl;
        cin >> answer;
    
        if (answer == 'y' || answer == 'Y'){
            rv = randomValueGeneration(mininum, maximum);
            diff1 = maximum - mininum;
            diff2 = rv - mininum;
            quartileClassification(diff2, diff1);
        } 
    }
  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}