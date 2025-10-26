#include "samodelkin.h"
#include <iostream>
#include <random>
using namespace std;

int generate_random_room_number(int* pGameRooms){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> intDist(1, *pGameRooms);
    return intDist(mt);
}

void empty_room(){
    cout << "You look around, there's nothing here" << endl;
}

void key_room(bool* hasKey){
    cout << "There doesn't seem to be much here, just a pile of things on the floor." << endl;
    if (*hasKey){
        cout << "You've already found the key." << endl;
        return;
    }

    char answer = 0;
    do{
        cout << "You notice something shiny in the corner.  Do you wish to pick it up? (Y/N): ";
        cin >> answer;
    }
    while (!(answer=='y'||answer=='Y'||answer=='n'||answer=='N'));

    if (answer=='y'||answer=='Y'){
        *hasKey = true;
        cout << "You've found a key!  Now to find what it goes to." << endl;
    } 
    else{
        cout << "You hope you don't regret that choice." << endl;
    }
}

void weapon_room(bool* hasWeapon){
    cout << "You appear to be in what was once an armory of sorts.  There are many broken weapons and shields scattered about." << endl;
    if (*hasWeapon) {
        cout << "You've already taken a weapon." << endl;
        return;
    }

    char answer = 0;
    do{
        cout << "Mounted upon the wall is the mighty sword Excalibur.  Do you wish to take it with you? (Y/N): ";
        cin >> answer;
    }
    while (!(answer=='y'||answer=='Y'||answer=='n'||answer=='N'));

    if (answer=='y'||answer=='Y'){
        *hasWeapon = true;
        cout << "You instantly feel more powerful." << endl;
    } 
    else{
        cout << "You hope you don't regret that choice." << endl;
    }
}

void armor_room(bool* pHasArmor){
    cout << "Hung upon a mannequin is a sturdy suit of armor." << endl;
    if (*pHasArmor){
        cout << "You've already donned armor." << endl;
        return;
    }

    char answer = 0;
    do{
        cout << "Do you wish to wear it? (Y/N): ";
        cin >> answer;
    }
    while (!(answer=='y'||answer=='Y'||answer=='n'||answer=='N'));

    if (answer=='y'||answer=='Y'){
        *pHasArmor = true;
        cout << "You feel safer already." << endl;
    } 
    else{
        cout << "You hope you don't regret that choice." << endl;
    }
}

void enemy_room(bool* hasWeapon, bool* pHasArmor, int* pGold, int* health, int* pGameState){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> monsterHealthDist(20, 35);
    int monsterHealth = monsterHealthDist(mt);

    cout << "There's a monster with " << monsterHealth << "HP in here!  Battle ensues!" << endl;

    while (monsterHealth > 0 && *health > 0){
        uniform_int_distribution<int> monsterDamageDist(5, 10);
        int monsterDamage = monsterDamageDist(mt);
        if (*pHasArmor) {
            monsterDamage = monsterDamage / 2;
            if (monsterDamage < 1) 
            {
                monsterDamage = 1;
            }
        }

        int playerDamage = 0;
        if (*hasWeapon){
            uniform_int_distribution<int> playerDamageDist(10, 15);
            playerDamage = playerDamageDist(mt);
            cout << "You swing Excalibur dealing " << playerDamage << " damage." << endl;
        } 
        else{
            uniform_int_distribution<int> playerDamageDist(1, 5);
            playerDamage = playerDamageDist(mt);
            cout << "You punch the beast dealing " << playerDamage << " damage." << endl;
        }
        monsterHealth -= playerDamage;

        if (monsterHealth > 0) {
            cout << "The beast beats you dealing " << monsterDamage << " damage." << endl;
            *health -= monsterDamage;
        }
    }

    if (*health <= 0){
        *pGameState = 3;
        cout << "You have been slain." << endl;
    } 
    else {
        uniform_int_distribution<int> goldDist(10, 30);
        int gp = goldDist(mt);
        *pGold += gp;
        cout << "You have slain the enemy and found " << gp << "GP." << endl;
    }
}

void potion_room(int *health){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> potionDist(5, 15);
    int healthPotion = potionDist(mt);

    cout << "A fountain flows in the middle of the room.  Cautiously you take a drink." << endl;
    cout << "You've restored " << healthPotion << "HP." << endl;
    *health += healthPotion;
}

void exit_room(bool *hasKey, int *pGameState){
    cout << "There's a massive locked gate blocking your way." << endl;
    if(*hasKey)
    {
        cout << "You try the key you found earlier.  It fits!" << endl;
        *pGameState = 2;
    } 
    else 
    {
        cout << "Perhaps you need to find a key somewhere?" << endl;
    }
}

void enter_room(int *roomNumber, int *health, bool *hasKey, bool *hasWeapon, bool* pHasArmor, int* pGold, int* pGameRooms, int *pGameState){
    cout << "You enter room #" << *roomNumber << ".  You have " << *health << "HP, Key = " 
         << (*hasKey? "Yes":"No") << ", Weapon = " << (*hasWeapon? "Yes":"No")
         << ", Armor = " << (*pHasArmor? "Yes":"No") << ", Gold = " << *pGold << "GP" << endl;

    if (*roomNumber == KEY){
        key_room(hasKey);
        return;
    }
    if (*roomNumber == WEAPON){
        weapon_room(hasWeapon);
        return;
    }
    if (*roomNumber == ARMOR){
        armor_room(pHasArmor);
        return;
    }
    if (*roomNumber == EXIT){
        exit_room(hasKey, pGameState);
        return;
    }

    int m = (*roomNumber) % 5;
    if (m == 1){
        empty_room();
    } 
    else if (m == 2){
        potion_room(health);
    } 
    else{
        enemy_room(hasWeapon, pHasArmor, pGold, health, pGameState);
    }
}
