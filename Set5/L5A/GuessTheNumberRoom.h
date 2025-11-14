#ifndef GUESS_THE_NUMBER_ROOM_H
#define GUESS_THE_NUMBER_ROOM_H

#include "Room.h"

class GuessTheNumberRoom : public ARoom {
public:
    GuessTheNumberRoom();
    ~GuessTheNumberRoom() override;

    bool escapeTheRoom() override;
private:
    int _secretNumber;
};

#endif//GUESS_THE_NUMBER_ROOM_H
