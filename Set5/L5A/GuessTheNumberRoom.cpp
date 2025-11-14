#include "GuessTheNumberRoom.h"

#include <iostream>
#include <limits>
#include <random>
using namespace std;

GuessTheNumberRoom::GuessTheNumberRoom() {
    cout << "GuessTheNumberRoom() called" << endl;

    mRoomName = "Guess The Number Room";
    random_device rd;
    mt19937 mt( rd() );
    uniform_int_distribution<int> dist(1, 20);
    _secretNumber = dist( mt );
}

GuessTheNumberRoom::~GuessTheNumberRoom() {
    cout << "~GuessTheNumberRoom() called" << endl;
}

bool GuessTheNumberRoom::escapeTheRoom() {
    cout << "Guess the secret number between 1 and 20. You get five tries." << endl;

    const int maxGuesses = 5;
    int guessesMade = 0;

    while (guessesMade < maxGuesses) {
        cout << "Enter guess #" << (guessesMade + 1) << ": ";
        int guess;
        if ( !(cin >> guess) ) {
            cout << "That isn't a number. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        ++guessesMade;

        if (guess < _secretNumber) {
            cout << "Too low!" << endl;
        } else if (guess > _secretNumber) {
            cout << "Too high!" << endl;
        } else {
            cout << "You guessed it! The door opens!" << endl;
            return true;
        }
    }

    cout << "You've run out of guesses! The number was " << _secretNumber << "." << endl;
    return false;
}
