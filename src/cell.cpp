#pragma once

#include "../headers/cell.h"

bool Cell::SetShip(Ship* ship) {
    if (!ship_) {
        ship_ = ship;
        return true;
    }
    return false;
}

char Cell::GetStatus() {
    if (ship_ && is_fired_) {
        return 'H';
    } else if (ship_) {
        return 'S';
    } else if (is_fired_) {
        return 'M';
    } else if (is_space_) {
        return ' ';
    }
    return '-';
}

void Cell::SetSpace() {
    is_space_ = true;
}

void Cell::Fire() {
    is_fired_ = true;
    if (ship_) {
        ship_->Hit();
    }
}
