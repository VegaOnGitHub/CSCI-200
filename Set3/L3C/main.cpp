/* CSCI 200: L3C
 *
 * Author: Daniel Vega
 *
 * deciphers secret 'moosage' using input and output files.
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <fstream>  // input and output files library.

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
  char c;
    ifstream inFile("secretMessage.txt");
    ofstream outFile("decipheredMessage.txt");

    if (inFile.fail()){
        cerr << "Couldn't open file" << endl;
        return -1;
    }

    while (inFile.get(c)){
      if (c == '\n'){
        outFile << '\n';
      } else if(c == '~'){
          outFile << ' ';
      } else {
          outFile << static_cast<char>(c + 1);
      }
    }



    inFile.close();
    outFile.close();

    
  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}
