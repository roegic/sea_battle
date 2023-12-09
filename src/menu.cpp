#include "headers/menu.h"

void drawTitle(){
    std::cout << "--------------------------------------------- \n";
    std::cout << "             EPIC SEA BATTLE GAME  \n";
    std::cout << "---------------------------------------------\n";
}

void showMenu(){

    std::cout << " 1. Start Game"<< std::endl;
    std::cout << " 2. Exit Game\n"<< std::endl;

    string command_type;
    string player_name;

    while (true) {
        std::cout<< "Select option(type in console 1 or 2): ";
        getline(cin, command_type);
        if(command_type == "1") { // пользователь нажал кнопку выход
            std::cout << "\x1B[2J\x1B[H" << std::endl;
            break;
        } else if (command_type == "2") {
            exit(0);
        }else {
            std::cout<< "Command is not correct. You should enter 1 or 2"<< std::endl;
        }
    }
    std::cout << " Enter player1 name: ";
    getline(cin,player_name);
    std::cout << "\n";
    std::cout << "\x1B[2J\x1B[H" << std::endl; // эта магия отчищает консоль, но работает на OSX только
    std::cout << " Enter player2 name: ";
    getline(cin,player_name);
    std::cout << "\n";
    std::cout << "\x1B[2J\x1B[H" << std::endl;
}
