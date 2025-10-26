#ifndef SAMODELKIN_H
#define SAMODELKIN_H

const int KEY = 3;
const int WEAPON = 7;
const int EXIT = 5;
const int ARMOR = 9;
const int ROOMS_DEFAULT = 10;

int generate_random_room_number(int* pGameRooms);
void empty_room();
void key_room(bool* hasKey);
void weapon_room(bool* hasWeapon);
void armor_room(bool* pHasArmor);
void enemy_room(bool* hasWeapon, bool* pHasArmor, int* pGold, int* health, int* pGameState);
void potion_room(int* health);
void exit_room(bool* hasKey, int* pGameState);
void enter_room(int* roomNumber, int* health, bool* hasKey, bool* hasWeapon, bool* pHasArmor, int* pGold, int* pGameRooms, int* pGameState);

#endif