#include <iostream>

/// 1. include fstream library
#include <fstream>
using namespace std;


int main() {
    // 2/3. declare and open file
    // ifstream fin;
    // fin.open("data.txt");

    // ifstream fin("./input/data.txt");

    ifstream fin("data.txt");
    ofstream fout;
    fout.open("output.txt");

    //4. Check for errors
    if (fin.fail()){ // if(!fin) or if(!fin.is_open())
        cerr << "Error opening input file" << endl;
        return -1;
    }
    if(!fout){
        cerr << "Error opening output file" << endl;
        return -1;
    }

    cout << "Hello World!" << endl;
    fout << "Hello World!" << endl;

    // 5. Read information from file
    int num;
    double dNum;
    char c;

    fin >> num >> dNum >> c;
    cout << num << " " << dNum << " " << c << endl;
    fout << num << " " << dNum << " " << c << endl;
    fin.get(c); // read the \n and ignore

    for (int i = 1; i <=4; i++){
        fin.get(c); // c = (char)fin.get();
        cout << c;
        fout << c;
    }

    // 6. close input/output file
    fin.close();
    fout.close();

    return 0;
}
