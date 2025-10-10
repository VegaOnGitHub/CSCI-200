/* CSCI 200: Lab 2B 
 *  
 * Pointer practice
 *
 * Author: Daniel Vega 
 *
 * Just an exercise that gets one more familier with how pointers word when it comes to using references and dereferences.
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {
    int iNum = 4;
    int iNum2 = 5;
    int* pINum1 = nullptr;
    int* pINum2 = nullptr;
    pINum1 = &iNum;
    pINum2 = &iNum2;

    cout << "address of iNum (passed by pointer): " << pINum1 << endl;
    cout << "address of iNum (passed by reference): " << &iNum << endl;
    cout << "address of iNum2 (passed by pointer): " << pINum2 << endl;
    cout <<  "address of iNum2 (passed by reference): " << &iNum2 << endl;
    

    iNum = 6;
    cout << "value of iNum (passed by value): " << iNum << endl;
    cout << "value of iNum (passed by pointer): " << *pINum1 << endl;

    *pINum1 = 7;
    cout << "value of iNum(changed value by pointer and passed by value): " << iNum << endl;

    pINum2 = pINum1;
    cout << "value of pINum2: " << pINum2 << endl;
    cout << "value pointed to by pINum2: " << *pINum2 << endl;

    *pINum2 = 8;
    cout << "value of iNum 3 different ways with the initial value of iNum2 being unchanged" << endl;
    cout << "*pINum1: " << *pINum1 << endl;
    cout << "*pINum2: " << *pINum2 << endl;
    cout << "iNum: " << iNum << endl;

    cout << "iNum2: " << iNum2 << endl;

    double* pDNum = nullptr;
 //     &iNum = dPNum;
 //     main.cpp:52:11: error: expression is not assignable

 //     Line 60 compiles but has a segmentation fault

 //     pDNum = pINum1;
 //     error: cannot convert ‘int*’ to ‘double*’ in assignment

    double dNum = 14.25;
    pDNum = &dNum;

    cout << "dPNum : " << pDNum << endl;
    cout << "*dPNum : " << *pDNum << endl;

    *pINum1 = *pDNum;

    cout << "*pINum1 after being assigned value of *pDNum: " << *pINum1 << endl;

    cout << "value of dNum (passed by value): " << dNum << endl;
    cout << "value of dNum (passed by pointer): " << *pDNum << endl;



  return 0; // signals the operating system that our program ended OK.
}