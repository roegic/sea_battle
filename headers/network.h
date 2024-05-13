#include <SFML/Network.hpp>
#include <iostream>
#include <string>

void start_multiplayer_game();
char create_connection();
void get_players_message();
std::pair<int,int> recieve_client_coords();
void send_coords_to_packet(int x, int y, int dir);
int send_client_direction(int direction);
int recieve_client_direction();
void send_packet();
std::vector<int> get_3_packet_data();
bool is_packet_recieved();