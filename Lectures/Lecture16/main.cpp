#include <fstream>
#include <iostream>
using namespace std;

const int SENTINAL_VALUE = -9999;

int main() {
    cout << "Hello World!" << endl;

    ifstream fin("data.txt");
    if( fin.fail() ) {
      cerr << "Could not open data.txt" << endl;
      return -1;
    }

    int value1, value5;
    double value2;
    char value3, value4;
    fin >> value1 >> value2 >> value3 >> value4 >> value5;

    cout << "Read: \"" << value1 << "\" \"" 
                       << value2 << "\" \""
                       << value3 << "\" \""
                       << value4 << "\" \""
                       << value5 << "\"" << endl;
  //Counter Controlled Input Loop
  int numLines, i1, i2;
  fin >> numLines;
  for(int i = 1; i <= numLines; i++){
    fin >> i1 >> i2;
    cout << i1 << " " << endl;
  }

  // Sentinel Controlled Input Loop
  while (true){
    fin >> i1;
    if(i1 == SENTINAL_VALUE){
      cout << "End of data reached" << endl;
      break;
    }
    cout << i1 << endl;
  }

  // End-Of-File Loop
  while(!fin.eof()){
    fin >> i1;
    cout << i1 << endl;
  }
    
    
    fin.close();

    return 0;
}
