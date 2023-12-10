#pragma once

#include "player.h"
#include <iostream>

using namespace std;

void AddShips (Player &player);
void GetCoordinatesFire(Player &player1, Player &player2);
void EnterToContinue();
void GetCoordinates(char &xc, char &yc);
void GetDirection(int &direction);
