/* Lecture 17 - Collections
 * Vectors - STL templated list
 * Strings - list of characters
 */

#include <cstddef>
#include <iostream>

// Add includes for the collections being used in your file
#include <vector>
#include <string>

using namespace std;

const int CLASS_SIZE = 3;

int main() {
    cout << "Collections - Vectors and Strings \n\n";

    // Declare a vector specifying the data type for the list
    vector<int> cwidList;

    // Declare and initialize a vector, size is CLASS_SIZE and all are set to the same value
    vector<double> gpaList(CLASS_SIZE, 4.0);
    // Declare and initialize a string / A vector of strings
    vector<string> nameList(CLASS_SIZE);
    string name = "";

    // Loop to enter CWIDs and names
    int cwid;
	double gpa;

    for (int i = 0; i < CLASS_SIZE; i++) {
        // Get CWID
        cout << "Enter CWID: ";
        cin >> cwid;

		// Get GPA
		cout << "Enter GPA: ";
		cin >> gpa;

        // Get first name
        cout << "Enter First Name: ";
        cin >> name;

        // add elements to back of list and grow the list
        cwidList.push_back(cwid);

        // Set the element at a position
        gpaList.at((size_t)i) = gpa;
        nameList.at((size_t)i) = name;
    }

    // Display CWIDs, names and grades
    for (size_t i = 0; i < cwidList.size(); i++) {
        cout << cwidList.at((size_t)i) << " " << nameList.at((size_t)i) << " " << gpaList.at((size_t)i) << endl;
    }

    // Element access is protected -- Access element 100
    cout << cwidList[3]; // don't do this!
    cout << cwidList.at(3);

    return 0;
}