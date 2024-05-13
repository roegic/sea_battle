#include "../headers/player.h"
#include <iostream>

void Player::CreateShip() {
    std::vector<std::string> shipName = {"Battleship","Cruiser","Destroyer", "Submarine"};
    std::vector<int> sizeShip = {4, 3, 2, 1};
    for (int i = 0; i < shipName.size(); ++i) {
        ships_.push_back(new Ship(sizeShip[i], shipName[i]));
    }
}

bool Player::FireEnemy(int x, int y) {
    if (field_.FireAtCell(x, y)) {
        return true;
    } else {
        return false;
    }
}


bool Player::PlaceShip(int x, int y, int direction, int idx) {
    return field_.PlaceShip(x, y, direction, ships_[idx]);
}

bool Player::IsWin() {
    if (hits_ == 0) {
        return true;
    }
    return false;
}

void Player::DecHits() {
    hits_--;
}

void Player::DrawHitFlield() {
    cout << "   ";
    string board_letters = "ABCDEFG";
    char letterH = 'H';
    for (int x = 0; x < 7; x++) {
        cout << board_letters[x] << "--";
    }
    cout << letterH << "\n";

    cout << "  ------------------------\n";
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << "| ";
        for (int j = 0; j < 8; j++) {
            if (field_.GetCellState(j, i) == 2) {
                cout << 'H' << "  ";
            } else if (field_.GetCellState(j, i) == 3) {
                cout << 'M' << "  ";
            } else {
                cout << '-' << "  ";
            }
        }
        cout << "|\n";
    }
    cout << "  ------------------------\n";
}

bool Player::IsHitTwice(int x, int y) {
    if (field_.GetCellState(x, y) == 2 || field_.GetCellState(x, y) == 3) {
        return true;
    } else {
        return false;
    }
}

void Player::SetPlayerName(string name) {
    name_ = name;
}

string Player::GetPlayerName() {
    return name_;
}

void Player::DrawField() {
    field_.DisplayField();
}