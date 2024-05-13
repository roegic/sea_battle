#pragma once

#include "player.h"
#include <iostream>
#include "network.h"

using namespace std;

void AddShips (Player &player, int type);
void GetCoordinatesFire(Player &player1, Player &player2);
void EnterToContinue();
void GetCoordinates(char &xc, char &yc, int type);
void GetDirection(int &direction, int type);
