#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include "Monopoly.cpp"
#include "Helper.cpp"


using namespace std;

int main(){
    // cout << "\n\n\n\n\n"
    //      << "Welcome to the University of Cincinnati!!!" << endl
    //      << "It's time to play some..." << endl
    //      << "_________ BEARCATOPOLY _________" << "\n\n"
    //      << "Phase 1 - Player Creation" << endl
    //      << "Enter the number of players: ";
    // int num_players;
    // cin >> num_players;
    // string player_name;
    // for(int i = 0; i < num_players; i++){
    //     cout << "Enter Player " << i+1 << "'s name (one word): ";
    //     cin >> player_name;
    //     Player player_temp(player_name);
    //     PLAYERS.push_back(player_temp);
    // }
    // cout << endl << "Phase 2 - Game Play" << endl;
    // int round_count = 1, choice, roll;
    // Player *current_player;
    // char input;
    // while(PLAYERS.size() > 1){
    //
    //     for(int z = 0; z < PLAYERS.size(); z++){
    //         current_player = &PLAYERS[z];
    //         choice = turnStartMenu(current_player);
    //
    //         if(choice == 1){
    //             cout << "Current position: " << current_player->getPos() << endl;
    //             cout << "Current location: " << BOARD[current_player->getPos()].getName() << endl;
    //             roll = rollDice();
    //             cout << "Your roll: " << roll << endl;
    //             current_player->move(roll);
    //
    //             // Location *current_location = BOARD + current_player->getPos();
    //             cout << "New position: " << current_player->getPos() << endl;
    //             // cout << "New location: " << current_location->getName() << endl;
    //             (BOARD + current_player->getPos())->buyLocation(current_player);
    //             cout << current_player->getName() << "'s money: " << current_player->getMoney() << endl;
    //
    //
    //             // if(current_location->getType() != "other"){
    //             //     if(current_location->isOwned()){
    //             //
    //             //     } else {
    //             //         cout << "You have landed on " << current_location->getName() << ". Would you like to buy it? (y/n)" << endl;
    //             //         cin >> input;
    //             //         if(input == 'y'){
    //             //             if(current_location->buyLocation(current_player)){
    //             //                 cout << "Congratulations! You have bought " << current_location->getName() << "!" << endl;
    //             //             } else {
    //             //                 cout << "You cannot buy " << current_location->getName() << "." << endl;
    //             //             }
    //             //         } else {
    //             //
    //             //         }
    //             //
    //             //
    //             //     }
    //             //
    //             //
    //             // }
    //
    //
    //         }
    //
    //
    //
    //
    //
    //
    //     }
    //
    // }

    Player bob("bob");
    Location* myptr;
    myptr = &Calhoun;
    myptr->buyLocation(&bob);
    cout << bob.getProperties().size() << endl;


}
