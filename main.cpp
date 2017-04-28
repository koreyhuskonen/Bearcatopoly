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
    cout << endl << "Phase 2 - Game Play" << endl;
    int round_count = 1, choice;
    Player *current_player;
    while(PLAYERS.size() > 1){

        for(int z = 0; z < PLAYERS.size(); z++){
            current_player = &PLAYERS[z];
            choice = menu(current_player);

            if(choice == 1){
                cout << "Current position: " << current_player->getPos() << endl;
                cout << "Current location: " << BOARD[current_player->getPos()].getName() << endl;
                int roll = rollDice();
                cout << "Your roll: " << roll << endl;
                current_player->move(roll);
                cout << "New position: " << current_player->getPos() << endl;
                cout << "New location: " << BOARD[current_player->getPos()].getName() << endl;
            }






        }

    }

}
