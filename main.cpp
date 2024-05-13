#include "headers/player.h"
#include "headers/game_update.h"
#include "headers/menu.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    Player player1;
    Player player2;
    player1.CreateShip();
    player2.CreateShip();
    DrawTitle();
    char type;
    ShowMenu(player1, player2, type);

    if (type == 'l') {
        AddShips(player2, 1);
        AddShips(player1, 1);
    }
    if (type == 'h') {
        AddShips(player1, 2);
    }
    if (type == 'j') {
        AddShips(player2, 3);
    }


    GetCoordinatesFire(player1, player2); // todo move it to addShip
}
