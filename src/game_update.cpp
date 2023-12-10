#pragma once

#include "../headers/game_update.h"

#include <vector>
#include <cctype>

void GetCoordinatesFire(Player &player1, Player &player2) {
    int turn = 1;
    while (true) {
        Player *selectedPlayer; // because we are storing
        Player *otherPlayer;
        if (turn % 2 == 0){
            selectedPlayer = &player1; // storing the memory address from the parameters into the new variables
            otherPlayer = &player2;
        } else{
            selectedPlayer = &player2;
            otherPlayer = &player1;
        }
        if (player1.IsLost()){
            cout << "\nPlayer " << player2.GetPlayerName() << " you won!" << endl;
            break;
        }
        if(player2.IsLost()){
            cout << "\nPlayer " << player1.GetPlayerName() << " you won!" << endl;
            break;
        }
        cout << "\nTurn: " << turn << "\nPlayer " << selectedPlayer->GetPlayerName() << " enter coordinates to Fire \n \n";  // playerName function returns the name_, since its the memory addresses passed through the parameters we must use ->
        otherPlayer->DrawHitFlield();

        char xc;
        char yc;
        while (true) {
            GetCoordinates(xc, yc);
            int x = toupper(xc) - 'A';  // similarly as the gameboard function this function will just update the table_
            int y = (yc - '0') - 1;
            if(!otherPlayer->IsHitTwice(x, y)){ // does the validation check
                if(otherPlayer->FireEnemy(x, y)){ // the memory addresses passed through the parameters we must use ->
                    cout << "It's a Hit!"<<endl;
                }else{
                    cout << "It's a miss!"<<endl;
                }
                break;
            }
            else{
                cout<<"Cannot shoot the same square twice, try again!"<<endl;
            }
        }
        cout<<"\n";
        EnterToContinue();
        turn++; // increase the turns once there has been a successful input from the user
    }
    cout<< "\n";
}

void GetDirection(int &direction) {
    char charDir; // will be used to store the first character
    std::vector<char> base = {'U','R','D','L'}; // char array that stores the compass direction
    string tempDirection;
    while (true) {
        cout<< "Enter the direction (U/R/D/L): ";
        getline(cin,tempDirection);
        if (!isalpha(tempDirection[0]) || tempDirection.size() != 1) {
            cout << "Invalid entry! Please try again." << endl;
            continue;
        }
        charDir = toupper(tempDirection[0]);// takes the first character of the string
        bool isValid = false;
        for (int i = 0; i < base.size(); ++i){
            if(base[i] == charDir){  // the toupper will convert the character to a upper case whilst going through the array
                direction = i + 1;
                isValid = true;
                break;
            }
        }
        if (!isValid) {
            cout << "Invalid entry! Please try again." << endl; // otherwise invalid and loop starts again
        } else {
            break;
        }
    }
}


void GetCoordinates(char &xc, char &yc) {
    while (true) {
        cout << "Enter the x coordinate [A-H][1-8]: ";
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
                cout << "Invalid entry! Please try again." << endl;
            } else if (!(toupper(x_enter[0]) - 'A' < 10 && toupper(x_enter[0]) - 'A' >= 0)) {
                cout << "Invalid entry! Please try again." << endl;
            } else if (!isdigit(x_enter[1])) {
                cout << "Invalid entry! Please try again." << endl;
            } else {
                xc = toupper(x_enter[0]);
                yc = x_enter[1];
                break;
            }
        } else {
            cout<< "Invalid entry! Please try again."<<endl;
        }
    }
}

void AddShips (Player &player) {
    // addship for the given player object
    std::string table = "--------------------------------------------- \n               Add Ship\n--------------------------------------------- \n           No  Name        table_\n--------------------------------------------- \n           1   Battleship   4 \n           2   Cruiser      3 \n           3   Destroyer    2 \n           4   Submarine    1 \n--------------------------------------------- \n";
    cout << table;

    std::vector<std::string> shipName = {"Battleship","Cruiser","Destroyer", "Submarine"};
    std::vector<int> sizeShip = {4, 3, 2, 1};
    char x_enter;
    char y_enter;
    int direction;

    for(int i = 0; i < shipName.size(); ++i) {
        for (int j = 0; j < 5 - sizeShip[i]; ++j) {
            while (true) {
                cout << player.GetPlayerName() << " add a " << shipName[i] << " size_: " << sizeShip[i] << endl;
                GetCoordinates(x_enter, y_enter);
                if (sizeShip[i] == 1) {
                    direction = 2;
                } else {
                    GetDirection(direction);
                }
                int x = toupper(x_enter) - 'A';
                int y = y_enter - '0' - 1;
                if (player.PlaceShip(x, y, direction, i)) {
                    break;
                } else {
                    cout << "The location of the ships_ is incorrect! \nShips should not overlap, go beyond borders, stand side by side or stand  corner by corner!\nPlease try again." << endl;
                }
            }
            cout << "\x1B[2J\x1B[H" << endl;
            player.DrawField();
            cout << "\n";
        }
    }
    cout<< "All ships_ are added!"<<endl;
    EnterToContinue(); // clears console in bash
}

void EnterToContinue() {     // this is just the press enter to continue function cin.clear doesnt work so i settled out for the clear bash console
    cout<<"Press enter to continue!";
    cin.ignore();
    cout << "\x1B[2J\x1B[H"<<endl; // clears console in bash
}
