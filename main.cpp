#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include "Monopoly.cpp"
#include "Helper.cpp"


using namespace std;

int main(){
    cout << "\n\n\n\n\n"
         << "Welcome to the University of Cincinnati!!!" << endl
         << "It's time to play some..." << endl
         << "_________ BEARCATOPOLY _________" << "\n\n"
         << "Phase 1 - Player Creation" << endl
         << "Enter the number of players: ";
    int num_players;
    cin >> num_players;
    string player_name;
    for(int i = 0; i < num_players; i++){
        cout << "Enter Player " << i+1 << "'s name (one word): ";
        cin >> player_name;
        Player player_temp(player_name);
        PLAYERS.push_back(player_temp);
    }
    int round_count = 1;
    PLAYERS[1].setPos(5000);
    Insomnia.buyLocation(&PLAYERS[1]);



    for(int i = 0; i < num_players; i++){
        cout << PLAYERS[i].getName() << "'s money: " << PLAYERS[i].getMoney() << endl;
        cout << PLAYERS[i].getName() << "'s position: " << PLAYERS[i].getPos() << endl;

    }


}
