#pragma once

#include "../headers/field.h"

#include <iostream>

Field::Field() {
    for (auto &columns: table_) {
        for (auto &cell: columns) {
            cell.SetShip(nullptr);
        }
    }
}

void Field::DisplayField() {
    std::cout << "   ";
    char alpha[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char alphaH = 'H';
    for (int x = 0; x < 7; x++) {
        std::cout << alpha[x] << "--";
    }
    std::cout << alphaH;
    std::cout << "\n";
    std::cout << "  ";
    for (int y = 0; y < 8; y++) {
        std::cout << "---";
    }
    std::cout << "\n";
    for (int i = 0; i < 8; i++) {
        std::cout << i + 1 << "| ";
        for (int j = 0; j < 8; j++) {
            std::cout << table_[i][j].GetStatus() << "  ";
        }
        std::cout << "|\n";
    }
    std::cout << "  ";
    for (int y = 0; y < 8; y++) {
        std::cout << "---";
    }
}

int Field::GetCellState(int x, int y) {
    if (table_[y][x].GetStatus() == ' ') {
        return 4;
    } else if (table_[y][x].GetStatus() == 'M') {
        return 3;
    } else if (table_[y][x].GetStatus() == 'H') {
        return 2;
    } else if (table_[y][x].GetStatus() == 'S') {
        return 1;
    }
    return 0;
}

bool Field::ValidateShip(int x, int y, int direction, Ship *ship) {
    if (GetCellState(x, y) == 1) {
        return false;
    }
    if ((direction == 2) && (x + (ship->GetSize() - 1) < 8)) {
        for (int i = 0; i < ship->GetSize(); i++) {
            if (GetCellState(x + i, y)) {
                return false;
            }
        }
        return true;
    } else if (direction == 4 && (x - (ship->GetSize() - 1) >= 0)) {
        for (int i = 0; i < ship->GetSize(); ++i) {
            if (GetCellState(x - i, y) == 0) {
                return false;
            }
        }
        return true;
    } else if (direction == 1 && (y - (ship->GetSize() - 1) >= 0)) {
        for (int i = 0; i < ship->GetSize(); ++i) {
            if (GetCellState(x, y - i)) {
                return false;
            }
        }
        return true;
    } else if (direction == 3 && (y + (ship->GetSize() - 1) < 8)) {
        for (int i = 0; i < ship->GetSize(); ++i) {
            if (GetCellState(x, y + i)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
//(U/R/D/L)
bool Field::PlaceShip(int x, int y, int direction, Ship *ship) {
    if (!ValidateShip(x, y, direction, ship)) {
        return false;
    }
    if (direction == 2) { //R
        for (int i = 0; i < ship->GetSize(); ++i) {
            table_[y][x + i].SetShip(ship);
            if (y - 1 >= 0) {
                table_[y - 1][x + i].SetSpace();
            }
            if (y + 1 < 8) {
                table_[y + 1][x + i].SetSpace();
            }
        }
        if (x - 1 >= 0) {
            for (int i = std::max(y - 1, 0); i <= std::min(y + 1, 7); ++i) {
                table_[i][x - 1].SetSpace();
            }
        }
        if (x + ship->GetSize() < 8) {
            for (int i = std::max(y - 1, 0); i <= std::min(y + 1, 7); ++i) {
                table_[i][x + ship->GetSize()].SetSpace();
            }
        }
        return true;
    } else if (direction == 4) { //L
        for (int i = 0; i < ship->GetSize(); i++) {
            table_[y][x - i].SetShip(ship);
            if (y - 1 >= 0) {
                table_[y - 1][x - i].SetSpace();
            }
            if (y + 1 < 8) {
                table_[y + 1][x - i].SetSpace();
            }
        }
        if (x - ship->GetSize() >= 0) {
            for (int i = std::max(y - 1, 0); i <= std::min(y + 1, 7); ++i) {
                table_[i][x - 1].SetSpace();
            }
        }
        if (x + 1 < 8) {
            for (int i = std::max(y - 1, 0); i <= std::min(y + 1, 7); ++i) {
                table_[i][x + 1].SetSpace();
            }
        }
        return true;
    } else if (direction == 1) { //U
        for (int i = 0; i < ship->GetSize(); i++) {
            table_[y - i][x].SetShip(ship);
            if (x - 1 >= 0) {
                table_[y - i][x - 1].SetSpace();
            }
            if (x + 1 < 8) {
                table_[y - i][x + 1].SetSpace();
            }
        }
        if (y - ship->GetSize() >= 0) {
            for (int i = std::max(x - 1, 0); i <= std::min(x + 1, 7); ++i) {
                table_[y - ship->GetSize()][i].SetSpace();
            }
        }
        if (y + 1 < 8) {
            for (int i = std::max(x - 1, 0); i <= std::min(x + 1, 7); ++i) {
                table_[y + 1][i].SetSpace();
            }
        }
        return true;
    } else if (direction == 3) { //D
        for (int i = 0; i < ship->GetSize(); i++) {
            table_[y + i][x].SetShip(ship);
            if (x - 1 >= 0) {
                table_[y + i][x - 1].SetSpace();
            }
            if (x + 1 < 8) {
                table_[y + i][x + 1].SetSpace();
            }
        }
        if (y - 1 >= 0) {
            for (int i = std::max(x - 1, 0); i <= std::min(x + 1, 7); ++i) {
                table_[y - 1][i].SetSpace();
            }
        }
        if (y + ship->GetSize() < 8) {
            for (int i = std::max(x - 1, 0); i <= std::min(x + 1, 7); ++i) {
                table_[y + ship->GetSize()][i].SetSpace();
            }
        }
        return true;
    }
    return false;
}

bool Field::FireAtCell(int x, int y) {
    if (table_[y][x].GetStatus() == 'S') {
        table_[y][x].Fire();
        return true;
    } else if (table_[y][x].GetStatus() == '-' || table_[y][x].GetStatus() == ' ') {
        table_[y][x].Fire();
        return false;
    }
    return false;
}
