#pragma once

#include "ship.h"
#include "cell.h"

class Field {
public:
    Field();
    void DisplayField();
    int GetCellState(int x, int y);
    bool ValidateShip(int x, int y, int direction, Ship* ship);
    bool PlaceShip (int x, int y, int direction, Ship* ship);
    bool FireAtCell (int x, int y);

private:
    Cell table_[8][8];
};
