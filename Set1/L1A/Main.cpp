/* CSCI 200: Lab 1A (L1A): (This is the math equation solver for lab 1 the equations I decided to use are THe Sheer Stress Equation and Coulomb)
 *
 * Author: Daniel Vega
 *
 *  I decided to do the 2 hardest equations for fun. In all honestly I have no clue what the equations do in nature
 *  but nonetheless I learned how to implement them in a C++ program.
 *  
 *  Description:
 *   - This program can calculate:
 *       1. Shear Stress on a plane
 *       2. Coulomb's Force magnitude
 *   - User is prompted to choose an equation and provide inputs.
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc. :3
#include <cmath> // for using sin, cos :3
#include <iomanip> // I only used setprecision :3

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.
const double PI = 3.1415926535897932384626433;
const double EPS0 = 8.854187817e-12;      // vacuum permittivity (F/m)

double degToRad(double deg){

    double radians = (deg * PI) / 180.00;

    return radians;

}


// τ_n = -½(σx - σy) sin(2θ) + τ_xy cos(2θ)   [θ in degrees]
double sheerOnPlane (double sigX, double sigY, double tauXY, double thetaDeg){

  double theta = degToRad(thetaDeg);
  double twoTheta = 2 * theta;
  double sheerStress = (-0.5 * (sigX - sigY) * sin(twoTheta) + tauXY * cos(twoTheta));
  
  return sheerStress;
}

// |F| = |qQ| / (4π ε0 εr r^2)
// Returns NaN if r <= 0 or eps_r <= 0
double coulombsForceMagnititude (double q, double Q, double r, double epsR){

  if (r <= 0.0 || epsR <= 0.0){
    return nan("");
  }

  double k = 1.0 /(4.0 * PI * EPS0 * epsR);
  double force = (k * fabs(q * Q) / (r * r));

  return force;
}

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
  cout << setprecision(6); 

  double choice, sigX, sigY, tauXY, thetaDeg; //inputs for sheer stress
  double q, Q, r, epsR; // inputs for Coulomb's Force

  //asks user which equation they would like to calculate for
  cout << "which of the following would you like to calculate!" << endl << "1. Sheer Stress" << endl << "2. Coulomb's Law" << endl;
  cin >> choice;

  if (choice == 1){

      cout << "Please Enter σx​ : ";

      if (!(cin >> sigX)){

        cerr << "Invalid!" << endl;
        return 1;

      }

      cout << "Please Enter σy​: ";

      if (!(cin >> sigY)) {

        cerr << "Invalid!" << endl;
        return 1;

      }

      cout << "Please Enter τn: ";

      if (!(cin >> tauXY)){

        cerr << "Invalid!" << endl;
        return 1;

      }
      cout << "Please Enter Theta in Degrees: ";

      if (!(cin >> thetaDeg)){

        cerr << "Invalid!" << endl;
        return 1;

      }

  double tauN = sheerOnPlane(sigX, sigY, tauXY, thetaDeg);

  cout << "\nThe Sheer Stress on τn​ at Theta = " << thetaDeg << " degrees is: " << tauN << endl;

  } else if (choice == 2){ 

    cout << "Please Enter Charge Q: ";

    if(!(cin >> Q)){

        cerr << "Invalid!";
        return 1;

    }

    cout << "Please Enter Charge q: ";

    if(!(cin >> q)){

        cerr << "Invalid!";
        return 1;

    }

    cout << "Please Enter Seperation r: ";

    if(!(cin >> r)){

        cerr << "Invalid!";
        return 1;

    }

    cout << "Please Enter Relative Permittivity of Medium: ";
    if(!(cin >> epsR)){

        cerr << "Invalid!";
        return 1;

    }
    
    double F = coulombsForceMagnititude(q, Q, r, epsR);
    if (isnan(F)){

      cerr << "Invalid Inputs for Coulombs Force (needs r > 0 and epsR > 0)" << endl;

    } else {

        cout << "Coulombs Force Magnitude |F|: " << F << endl;

    }


  } else {

    cout << "Invalid Choice!" << endl;

  }


  /******** INSERT YOUR CODE ABOVE HERE ********/


  return 0; // signals the operating system that our program ended OK.
}
