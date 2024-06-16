#pragma once

#include "../headers/game_update.h"

#include <vector>
#include <cctype>
#include <tuple>

string invalid_input = "Invalid input! Please try again";
vector<pair<int, int>> client_field;
vector<int> client_directions;
vector<pair<int, int>> server_field;
vector<int> server_directions;
int SHIPS_CNT = 10;

pair<int,int> get_fire_coords_from_other() {
  int x=0;
  int y=0;
  while (true) {
    if (is_packet_recieved()) {
      pair<int,int> coords_received = get_fire_coords_packet();
      x = coords_received.first;
      y = coords_received.second;
      break;
    }
  }
  return {x,y};
}



void GetCoordinatesFire(Player &player1, Player &player2, int type) {
    int turn = 1;

//    if (type == 3) { // первым начинает клиент
//      cout << "\nTurn: " << turn << "\nPlayer " << player2.GetPlayerName()
//           << " enter coordinates to Fire \n \n";
//    }
    while (true) {
        Player *selectedPlayer;
        Player *otherPlayer;
        if (turn % 2 == 0) {
            selectedPlayer = &player1;
            otherPlayer = &player2;
        } else {
            selectedPlayer = &player2;
            otherPlayer = &player1;
        }
        if (player2.IsWin()) {
            if (type == 0) {
                if (player2.GetPlayerName() == "Computer") {
                    cout << "\nPlayer " << player1.GetPlayerName() << " you lose!" << endl;
                    break;
                }
            }
            cout << "\nPlayer " << player2.GetPlayerName() << " you won!" << endl;
            break;
        }
        if (player1.IsWin()) {
            if (type == 0) {
                if (player1.GetPlayerName() == "Computer") {
                    cout << "\nPlayer " << player2.GetPlayerName() << " you lose!" << endl;
                    break;
                }
            }
            cout << "\nPlayer " << player1.GetPlayerName() << " you won!" << endl;
            break;
        }
//        cout << "\nTurn: " << turn << "\nPlayer " << selectedPlayer->GetPlayerName()
//             << " enter coordinates to Fire \n \n";
        //todo это не работает
        if (type == 3) {
            if (turn % 2 == 1) {
                otherPlayer->DrawHitFlield();
            } else {
                selectedPlayer->DrawHitFlield();
            }
        }
        if (type == 2) {
            if (turn % 2 == 0) {
                otherPlayer->DrawHitFlield();
            } else {
                selectedPlayer->DrawHitFlield();
            }
        }
        if (type == 1 || type == 0) {
            otherPlayer->DrawHitFlield();
        }
        cout << "\nTurn: " << turn << "\nPlayer " << otherPlayer->GetPlayerName()
             << " enter coordinates to Fire \n \n";



        char xc;
        char yc;
        while (true) {
            int x,y;
            if (type == 1 || (type == 0 && otherPlayer->GetPlayerName() != "Computer")) {
                GetCoordinates(xc, yc, type);
                x = toupper(xc) - 'A';
                y = (yc - '0') - 1;
            }
            if (type == 0) {
                if (otherPlayer->GetPlayerName() == "Computer") {
                    x = rand() % 8;
                    y = rand() % 8;
                    cout << "Computer hits " << char(x + 'A') << char(y + 1 + '0') <<'\n';
                }
            }
            if (type == 2) { // хост
                if (turn %2 == 0) { //ход хоста
                    GetCoordinates(xc, yc, type);
                    x = toupper(xc) - 'A';
                    y = (yc - '0') - 1;
                    send_fire_coords_to_packet(x,y);
                } else { // ждем ответа от клиента
                    pair<int,int> fire_coords = get_fire_coords_from_other();
                    x = fire_coords.first;
                    y=fire_coords.second;
                    int t =0;
                }
            }
            if (type == 3) { // client
                if (turn %2 == 1) { // clients move
                    GetCoordinates(xc, yc, type);
                    x = toupper(xc) - 'A';
                    y = (yc - '0') - 1;
                    send_fire_coords_to_packet(x,y);
                } else { // ждем ответа от host
                    pair<int,int> fire_coords = get_fire_coords_from_other();
                    x = fire_coords.first;
                    y=fire_coords.second;
                    int t =0;
                }
            }


            if (!otherPlayer->IsHitTwice(x, y)) {
                if (otherPlayer->FireEnemy(x, y)) {
                    cout << "It's a Hit!" << endl;
                    turn--;
                    otherPlayer->DecHits();
                } else {
                    cout << "It's a miss!" << endl;
                }
                break;
            } else {
                cout << "You are trying shoot the same square twice, try again!"
                     << endl;
            }
        }
        cout << "\n";
        EnterToContinue();
        turn++;

    }
    cout << "\n";
}

void GetDirection(int &direction, int type) {
    char charDir;
    std::vector<char> base = {'U', 'R', 'D', 'L'};
    string tempDirection;
    while (true) {
        cout << "Enter the direction (U/R/D/L): ";
        getline(cin, tempDirection);
        if (!isalpha(tempDirection[0]) || tempDirection.size() != 1) {
            cout << invalid_input << endl;
            continue;
        }
        charDir = toupper(tempDirection[0]);
        bool isValid = false;
        for (int i = 0; i < base.size(); ++i) {
            if (base[i] == charDir) {
                direction = i + 1;
                isValid = true;
                break;
            }
        }
        if (!isValid) {
            cout << invalid_input << endl;
        } else {
            break;
        }
    }
}


void GetCoordinates(char &xc, char &yc, int type) {
    while (true) {
        cout << "Enter the coordinate [letter(A-H)][number(1-8)] (example: A1): ";
        std::string xcord;
        getline(cin,xcord);
        string x_enter;
        for (int i = 0; i < xcord.size(); ++i) {
            if (!isspace(xcord[i])) {
                x_enter += xcord[i];
            }
        }
        if (x_enter.length() == 2) {
            if (!isalpha(x_enter[0])) {
                cout << invalid_input << endl;
            } else if (!(toupper(x_enter[0]) - 'A' < 9 &&
                         toupper(x_enter[0]) - 'A' >= 0)) {
                cout << invalid_input << endl;
            } else if (!isdigit(x_enter[1])) {
                cout << invalid_input << endl;
            } else if (x_enter[1] - '0' < 1 || x_enter[1] - '0' >= 9) {
                cout << invalid_input << endl;
            } else {
                xc = toupper(x_enter[0]);
                yc = x_enter[1];

                break;
            }
        } else if (xcord != ""){
            cout << invalid_input << endl;
        }
    }
}

void send_to_client() {
  int cur_idx=0;
  std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer",
                                       "Submarine"};
  std::vector<int> sizeShip = {4, 3, 2, 1};
  for (int i = 0; i < shipName.size(); ++i) {
    for (int j = 0; j < 5 - sizeShip[i]; ++j) {
      send_coords_to_packet(server_field[cur_idx].first,
                            server_field[cur_idx].second,
                            server_directions[cur_idx]);
      cur_idx++;
    }
  }
  send_packet();
}

void send_to_host() {
  int cur_idx=0;
  std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer",
                                       "Submarine"};
  std::vector<int> sizeShip = {4, 3, 2, 1};
  for (int i = 0; i < shipName.size(); ++i) {
    for (int j = 0; j < 5 - sizeShip[i]; ++j) {
      send_coords_to_packet(client_field[cur_idx].first,
                            client_field[cur_idx].second,
                            client_directions[cur_idx]);
      cur_idx++;
    }
  }
  send_packet();
}

void get_field_from_client(Player &other_player) {

  int cur_idx=0;
  std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer",
                                       "Submarine"};
  std::vector<int> sizeShip = {4, 3, 2, 1};

  while (true) {
    if(is_packet_recieved()) {
      for (int i = 0; i < shipName.size(); ++i) {
        for (int j = 0; j < 5 - sizeShip[i]; ++j) {
          client_field.push_back({0, 0});
          client_directions.push_back(0);
          vector<int> data = get_3_packet_data();
          client_field[cur_idx].first = data[0];
          client_field[cur_idx].second = data[1];
          client_directions[cur_idx] = data[2]; //todo these are for debug only
          int x= data[0];
          int y=data[1];
          int direction = data[2];
          other_player.PlaceShip(x, y, direction, i);
          cur_idx++;
        }
      }
      break;
    }
  }
}
void get_field_from_host(Player &other_player) {

  int cur_idx=0;
  std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer",
                                       "Submarine"};
  std::vector<int> sizeShip = {4, 3, 2, 1};

  while (true) {
    if(is_packet_recieved()) {
      for (int i = 0; i < shipName.size(); ++i) {
        for (int j = 0; j < 5 - sizeShip[i]; ++j) {
          server_field.push_back({0, 0});
          server_directions.push_back(0);
          vector<int> data = get_3_packet_data();
          server_field[cur_idx].first = data[0];
          server_field[cur_idx].second = data[1];
          server_directions[cur_idx] = data[2]; //todo server_field and server_dir are for debug only
          int x= data[0];
          int y=data[1];
          int direction = data[2];
          other_player.PlaceShip(x, y, direction, i);
          cur_idx++;
        }
      }
      break;
    }
  }
}

void AddShips(Player &player, Player &other_player, int type) {
  // addship for the given player object
  std::string table =
      "--------------------------------------------- \n               Add "
      "Ship\n--------------------------------------------- \n           No  "
      "Name        size\n--------------------------------------------- \n      "
      "     1   Battleship   4 \n           2   Cruiser      3 \n           3  "
      " Destroyer    2 \n           4   Submarine    1 "
      "\n--------------------------------------------- \n";
  cout << table;

  std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer",
                                       "Submarine"};
  std::vector<int> sizeShip = {4, 3, 2, 1};
  char x_enter;
  char y_enter;
  int direction;

  for (int i = 0; i < shipName.size(); ++i) {
    for (int j = 0; j < 5 - sizeShip[i]; ++j) {
      while (true) {
        cout << player.GetPlayerName() << " add a " << shipName[i]
             << " size: " << sizeShip[i] << endl;
        GetCoordinates(x_enter, y_enter, type);
        if (sizeShip[i] == 1) {
          direction = 2;
        } else {
          GetDirection(direction, type);
        }
        int x = toupper(x_enter) - 'A';
        int y = y_enter - '0' - 1;
        if (type == 2) {
          server_field.push_back({x, y});
          server_directions.push_back({direction});
        }
        if (type == 3) {
          client_field.push_back({x, y});
          client_directions.push_back({direction});
        }
        if (player.PlaceShip(x, y, direction, i)) {
          break;
        } else {
          cout << "The location of the ships is incorrect! \nShips should not "
                  "overlap, go beyond borders!\nPlease try again."
               << endl;
        }
      }
      cout << "\x1B[2J\x1B[H" << endl;
      player.DrawField();
      cout << "\n";
    }
  }
  if (type == 2) { // type = 2 means it is host we need to get clients data
    get_field_from_client(other_player);
    send_to_client();

  }
  if (type == 3) { // type = 3 means it is client we need to get clients data
    send_to_host();
    get_field_from_host(other_player);
  }
  if (type == 0) {
      PlaceShipsAutomatically(other_player);
  }

  cout << "All ships are added!" << endl;
  EnterToContinue();

//  if (type == 1) {
//    GetCoordinatesFire(player, other_player, 1);
//  }

  if (type == 2) {
    GetCoordinatesFire(player, other_player, 2); // todo move it to addShip
  } else if (type == 3) {
    GetCoordinatesFire(other_player, player, 3); // todo move it to addShip
  }

}

void EnterToContinue() {
  cout<<"Press enter to continue!";
  cin.ignore();
  cout << "\x1B[2J\x1B[H"<<endl;
}

void PlaceShipsAutomatically(Player &player) {
    std::vector<std::string> shipName = {"Battleship", "Cruiser", "Destroyer", "Submarine"};
    std::vector<int> sizeShip = {4, 3, 2, 1};
    std::vector<int> shipCount = {1, 2, 3, 4};  // Количество кораблей каждого типа

    srand(time(0));

    for (int i = 0; i < shipName.size(); ++i) {
        for (int j = 0; j < shipCount[i]; ++j) {
            while (true) {
                int x = rand() % 8;
                int y = rand() % 8;
                int direction = rand() % 4 + 1; // 1: Up, 2: Right, 3: Down, 4: Left
                if (player.PlaceShip(x, y, direction, i)) {
                    break;
                }
            }
        }
    }
}