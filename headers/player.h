#pragma once

#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"

using namespace std;
class Player {
private:
    string name;
    Field field;
    vector<Ship *> ships;
public:
    void draw_field();

    void set_player_name(string name);

    string get_player_name();
    bool fire_enemy(int x, int y);
    bool place_ship(int x, int y, int direction, int idx);
    bool is_lost_check();

    void drawEnemyField(); // показывает черновик что где может быть у противника
    bool isHitTwice(int xcord, int ycord);

    void create_ships();
};