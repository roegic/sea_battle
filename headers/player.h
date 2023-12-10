#pragma once

#include <string>
#include <vector>
#include "field.h"
#include "ship.h"

using namespace std;
class Player {
private:
    string name_;
    Field field_;
    vector<Ship *> ships_;
public:
    void DrawField();

    void SetPlayerName(string name);

    string GetPlayerName();

    bool FireEnemy(int x, int y);

    bool PlaceShip(int x, int y, int direction, int idx);

    bool IsLost();


    void DrawHitFlield();  // показывает черновик что где может быть у противника

    bool IsHitTwice(int x, int y);

    void CreateShip();
};