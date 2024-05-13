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

  AddShips(player2, 1);
  AddShips(player1, 1);



  GetCoordinatesFire(player1, player2); // todo move it to addShip
}
