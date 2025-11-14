#include "Room.h"

#include <iostream>
using namespace std;

ARoom::ARoom() {
    cout << "ARoom() called" << endl;

    mRoomName = "Vacant Room";
}

ARoom::~ARoom() {
    cout << "~ARoom() called" << endl;
}

string ARoom::getRoomName() const {
    return mRoomName;
}

bool ARoom::escapeTheRoom() {
    cout << "There's no escape" << endl;
    return false;
}
