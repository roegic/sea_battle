#include "headers/player.h"
#include <iostream>

void Player::create_ships() {
    std::vector<std::string> shipName = {"Battleship","Cruiser","Destroyer", "Submarine"};
    std::vector<int> sizeShip = {4, 3, 2, 1};
    for (int i = 0; i < shipName.size(); ++i) {
        ships.push_back(); // todo add ship creation
    }
}

bool Player::fire_enemy(int x, int y) {
    return false; // todo add implementation
}


bool Player::place_ship(int x, int y, int direction, int idx) {
    return false; // todo add implementation
}

bool Player::is_lost_check() {
    return false; // todo add implementation
}


void Player::drawEnemyField() {
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
            if (0) {
                cout << 'H' << "  "; // todo add implementation
            } else if (0) {
                cout << 'M' << "  "; // todo add implementation
            } else {
                cout << '-' << "  ";
            }
        }
        cout << "|\n";
    }
    cout << "  ------------------------\n";
}

bool Player::isHitTwice(int xcord, int ycord) {
    return false; // todo add implementation
}

void Player::set_player_name(string name) {
    this->name = name;
}

string Player::get_player_name() {
    return name;
}

void Player::draw_field() {
    // todo add implementation
}