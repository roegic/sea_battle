#pragma once

#include "ship.h"

class Cell{
public:
    bool SetShip(Ship* ship);
    char GetStatus();
    void Fire();
    void SetSpace();

private:
    Ship* ship_ = nullptr;
    bool is_fired_ = false;
    bool is_space_ = false;
};
