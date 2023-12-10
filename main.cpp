#include "headers/player.h"
#include "headers/game_update.h"
#include "headers/menu.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    Player player1;  // creating my player objects
    Player player2;
    player1.CreateShip();
    player2.CreateShip();
    DrawTitle();
    ShowMenu(player1, player2); // allow the players to enter their names

    AddShips(player1); // allows the players to enter their ships_
    AddShips(player2);
    GetCoordinatesFire(player1, player2); // allows separate players to Hit against each others boards
}
