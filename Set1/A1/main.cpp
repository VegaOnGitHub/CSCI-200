/*
 * CSCI 200: Assignment 1 - A1 
 * Author: Daniel Vega
 *
 * Resources used: C++ reference (cplusplus.com / cppreference.com). just helps navigate the standard library, coded this along with my roommate who also has the same class.
 * We both have completely different code, his name is jacob horton if you'd like to fact check. mainly exganged ways we approached certain parts of the program.
 *
 * Honor code: I, Daniel Vega, affirm that I have neither given nor received
 * unauthorized assistance on this assignment.
 *
 * Description: Slot machine, you start with 100 dollars taken directly from your childs college fund
 * and you gamble it all (drinking is highly recommended as well while gambling)
 * you triple your bet amount if you get 2 adjacent numbers correct and 10x your bet if you get all 3 numbers
 * money won it added back into your bank roll, it then asks the user again if they would like to roll again
 * the user who knows 99% of gamblers quit after their next big hit most likely will roll again
 * once the user is out of money, they then get kicked out dramtically and left on the street since their wife has left them.
 * If the user has a sense of reason, they may also cash out and told to have a nice day.
 * I was going to go for extra credit but im honestly already too tired from this 
 * since this was actually a little harder and time consuming
 * then I planned for it to be. Also I played it few times and got up to $24960 which I find kind of funny
 * some other things i'd like to mention is that it would've been easier to pass by referece in my
 * function which we haven't really learned which actually made it a bit harder.
 * I also didn't know if I could use the cctype header which would've made the asciiLower function
 * usless since it effectively already exists in that header. and the string header was effectively a need.
 * also prompting the user what the number range the wheel should output
 * instead of having it from 1-9 automatically is kind of stupid but i digress. 
 * 
 */



// The include section adds extra definitions from the C++ standard library.
#include <iostream> // for cin, cout, etc.
#include <random> // for mt19937
#include <string> // in order to use it as a parameter in my functions and also using it for user input.

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

void flushLine() {

    char ch;

    while (cin.get(ch) && ch != '\n'){}

}


int readInt(string prompt) {

    while (true) {

        cout << prompt;
        int x;
        if (cin >> x) {
            return x;
        }
        cin.clear();
        flushLine();
    }
}

char readChar(string prompt) {

    while (true) {

        cout << prompt;
        string s;
        if (cin >> s && !s.empty()) {
            return s[0];
        }
        cin.clear();
        flushLine();
    }
}

// ASCII-only function
char asciiLower(char c) {
    if (c >= 'A' && c <= 'Z'){

     return static_cast<char>(c - 'A' + 'a');

     }

    return c;
}
// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
    int bank = 100;

    int minWheel = readInt("What is the minimum wheel value? ");
    int maxWheel = readInt("What is the maximum wheel value? ");

    while (maxWheel < minWheel + 9) {

        cout << "Please ensure the maximum is at least 9 more than the minimum.\n";
        maxWheel = readInt("What is the maximum wheel value? ");

    }

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(minWheel, maxWheel);

    while (true) {
        if (bank <= 0) {
        
            cout << "Time for you to go\n";
            break;
        }

        cout << "You have $" << bank << ", how much do you wish to wager? ";
        int bet;

    while (true) {

        if (cin >> bet) {

            if (bet > 0 && bet <= bank) {
                break;
            }

    cout << "Please enter a positive wager no greater than your bank amount of $" << bank << "";

    } else {
        cin.clear(); 
        flushLine(); 
        cout << "Please enter a valid integer wager: ";
    }
}

    int a = dist(mt);
    int b = dist(mt); 
    int c = dist(mt);

    cout << "Result: " << a << " " << b << " " << c << endl;

    bool allThree = (a == b && b == c);
    bool anyTwo   = (!allThree) && (a == b || a == c || b == c);

    if (allThree) {
        cout << "JACKPOT!" << endl;
        bank += bet * 10;
    } else if (anyTwo) {
        cout << "Winner" << endl;
        bank += bet * 3;
    } else {
        cout << "Better luck next time" << endl;
        bank -= bet;
    }

    cout << "You now have $" << bank << endl;
        
    if (bank <= 0) {
        cout << "Time for you to go lil bro, today anit your day gng </3" << endl;
        cout << "Wife: I'm leaving you and taking the kids!" << endl;
        break;
    }

    char choice = readChar("What do you wish to do?\nR - roll again\nC - cash out\n");

    choice = asciiLower(choice);

    while (choice != 'r' && choice != 'c') {

        choice = asciiLower(readChar("Please enter R to roll again or C to cash out: "));

    }

    if (choice == 'c') {

        cout << "Have a nice day!" << endl;
        break;

    }
}
    /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}
