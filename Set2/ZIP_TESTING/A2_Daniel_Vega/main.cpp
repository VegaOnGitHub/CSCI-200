/* CSCI 200: A2
 *
 * Author: Daniel Vega
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include "samodelkin.h" // functions created

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  /******** INSERT YOUR CODE BELOW HERE ********/
    bool hasKey = false;
    bool* pHasKey = &hasKey;
    bool hasWeapon = false;
    bool* pHasWeapon = &hasWeapon;
    bool hasArmor = false;
    bool* pHasArmor = &hasArmor;
    int gold = 0;
    int* pGold = &gold;
    int health = 100;
    int* pHealth = &health;
    int gameRooms = ROOMS_DEFAULT;
    int* pGameRooms = &gameRooms;
    int gameState = 1; 
    int* pGameState = &gameState;

    cout << "Difficulties:" << endl;
    cout << "(1) Easy" << endl;
    cout << "(2) Medium" << endl;
    cout << "(3) Hard" << endl;
    cout << "(4) Insane" << endl;

    int diff = 0;
    while ((diff < 1 || diff > 4)){
        cout << "Select game difficulty: ";
        cin >> diff;
        if (cin.fail()) {
        cerr << "Invalid input. Returning 0." << endl;
        return 0; 
    }
        
        
    }
    if (diff == 1){
        *pGameRooms = 10;
    }
    if (diff == 2){
        *pGameRooms = 25;
    }
    if (diff == 3){
        *pGameRooms = 50;
    }
    if (diff == 4){
        *pGameRooms = 100;
    } 

    int roomsExplored = 0;

    while (*pGameState == 1) {
        int room = generate_random_room_number(pGameRooms);

        cout << "You continue deeper into the dungeon, this time exploring Room #" << room << endl;

        enter_room(&room, pHealth, pHasKey, pHasWeapon, pHasArmor, pGold, pGameRooms, pGameState);

        roomsExplored++;

        if (*pGameState == 1){
            char c = 0;
            do{
                cout << "Do you wish to continue exploring? (Y/N): ";
                cin >> c;
            } 
            while (!(c=='y'||c=='Y'||c=='n'||c=='N'));
            if (c=='n'||c=='N'){
                *pGameState = 4;
            }
        }
    }

    if (*pGameState == 2){
        cout << "After visiting " << roomsExplored << " rooms and finding " << *pGold << "GP, you have finally escaped alive!" << endl;
    } 
    else if (*pGameState == 3){
        cout << "After visiting " << roomsExplored << " rooms and finding " << *pGold << "GP, you have met an untimely end." << endl;
        cout << "Maybe you will some day find the key to unlock the gate." << endl;
        cout << "Perhaps a sword could make the escape quicker." << endl;
        cout << "Perhaps you would have stayed longer with some armor." << endl;
    } 
    else if (*pGameState == 4){
        cout << "After visiting " << roomsExplored << " rooms and finding " << *pGold << "GP, you have given up, forever destined to wander the dungeon." << endl;
        cout << "Key = " << (hasKey? "Yes":"No") << ", Weapon = " << (hasWeapon? "Yes":"No") << ", Armor = " << (hasArmor? "Yes":"No") << endl;
        cout << "Maybe you will some day find the key to unlock the gate." << endl;
        cout << "Perhaps a sword could make the escape quicker." << endl;
        cout << "Perhaps you would have stayed longer with some armor." << endl;
    }

  /******** INSERT YOUR CODE ABOVE HERE ********/

  return 0; // signals the operating system that our program ended OK.
}