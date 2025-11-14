#include "GuessTheNumberRoom.h"
#include "ExitRoom.h"

#include <iostream>
#include <random>
using namespace std;

ARoom* go_to_next_room(int randRoomChoice) {
    if (randRoomChoice == 7) {
        return new ExitRoom();
    }

    return new GuessTheNumberRoom();
}

int main() {
    random_device rd;
    mt19937 mt( rd() );
    uniform_int_distribution<int> dist(1, 10);

    ARoom* currentRoom = nullptr;

    while (true) {
        delete currentRoom;
        currentRoom = go_to_next_room( dist(mt) );
        cout << "Welcome to the " << currentRoom->getRoomName() << endl;

        if ( currentRoom->escapeTheRoom() ) {
            break;
        }
    }

    cout << "You made it out!" << endl;
    delete currentRoom;
    currentRoom = nullptr;

    return 0;
}
