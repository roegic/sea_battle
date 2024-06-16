#include "headers/player.h"
#include "headers/game_update.h"
#include "headers/menu.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    while (true) {
        Player player1;
        Player player2;
        player1.CreateShip();
        player2.CreateShip();
        DrawTitle();
        char type;
        ShowMenu(player1, player2, type);

        if (type == 'l') {
            AddShips(player1, player2, 1);
            AddShips(player2, player1, 1);
            GetCoordinatesFire(player1, player2, 1);
        } else if (type == 'h') {
            AddShips(player1, player2, 2);
            GetCoordinatesFire(player1, player2, 2); // todo move it to addShip
        } else if (type == 'j') {
            AddShips(player2, player1, 3);
            GetCoordinatesFire(player1, player2, 3); // todo move it to addShip
        } else if (type = 'c') {
            AddShips(player1, player2, 0);
            GetCoordinatesFire(player1, player2, 0);
        }
    }
}
