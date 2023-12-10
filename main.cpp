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
    ShowMenu(player1, player2);

    AddShips(player1);
    AddShips(player2);
    GetCoordinatesFire(player1, player2);
}
