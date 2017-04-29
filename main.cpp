#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
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
    string player_name, input;
    int num_players;
    getline(cin, input);
    stringstream(input) >> num_players;
    for(int i = 0; i < num_players; i++){
        cout << "Enter Player " << i+1 << "'s name: ";
        getline(cin, player_name);
        Player player_temp(player_name);
        PLAYERS.push_back(player_temp);
    }
    cout << endl << "Phase 2 - Game Play" << endl;
    int round_count = 1, choice, roll;
    Player *current_player;
    while(PLAYERS.size() > 1){

        for(int z = 0; z < PLAYERS.size(); z++){
            cout << endl;
            current_player = &PLAYERS[z];
            choice = turnStartMenu(current_player);
            cout << "CHOICE: " << choice << endl;
            if(choice == 1){
                cout << "Current position: " << current_player->getPos() << endl;
                cout << "Current location: " << BOARD[current_player->getPos()]->getName() << endl;
                // roll = rollDice();
                // cout << "Your roll: " << roll << endl;

                cout << "Enter your roll: ";
                getline(cin, input);
                stringstream(input) >> roll;
                current_player->move(roll);

                Location *current_location = BOARD[current_player->getPos()];
                cout << "New position: " << current_player->getPos() << endl;
                cout << "New location: " << current_location->getName() << endl;
                cout << current_player->getName() << "'s money: " << current_player->getMoney() << endl;

                if(current_location->getType() != "other"){
                    cout << "You landed on " << current_location->getName() << "." << endl;
                    if(current_location->isOwned()){
                        cout << current_location->getOwner() << " already owns this property. You'll have to pay rent." << endl;
                        if(current_location->getType() == "eatery"){
                            current_location->payRent(current_player, roll);
                            cout << "You paid $" << current_location->getRent(roll) << endl;
                        } else {
                            current_location->payRent(current_player);
                            cout << "You paid $" << current_location->getRent() << endl;
                        }
                    } else {
                        cout << "Would you like to buy it? (y/n)" << endl;
                        getline(cin, input);
                        if(input == "y"){
                            if(current_location->buyLocation(current_player)){
                                cout << "Congratulations! You bought " << current_location->getName() << "!" << endl;
                            } else {
                                cout << "You cannot buy " << current_location->getName() << "." << endl;
                            }
                        }
                    }
                } else if(current_location->getName() == "Bearcat Card"){
                    cout << "You landed on a Bearcat Card!" << endl;
                    cout << "The card says: ";
                    drawCard(current_player);
                }
            } else if(choice == 2){
                current_player->displayProperties();
            } else if(choice == 3){
                cout << "Enter the name of the property you'd like to sell: ";
                string property_name; Location *selected_location = NULL;
                getline(cin, property_name);
                for(int i = 0; i < 40; i++){
                    if(BOARD[i]->getName() == property_name) selected_location = BOARD[i];
                }
                if(!selected_location){
                    cout << "You did not enter a valid property name." << endl;
                } else if(selected_location->sellLocation(current_player)){
                    cout << "You sold " << selected_location->getName() << " for $" << selected_location->getMortgage() << "." << endl;
                } else {
                    cout << "You cannot sell a property that you do not own." << endl;
                }
            } else if(choice == 4){
                cout << "Enter the name of the property you'd like to build houses on: ";
                string property_name; Location *sl = NULL;
                getline(cin, property_name);
                for(int i = 0; i < 40; i++){
                    if(BOARD[i]->getName() == property_name && BOARD[i]->getType() == "property") sl = BOARD[i];
                }
                if(!sl){
                    cout << "You did not enter a valid property name." << endl;
                } else if(dynamic_cast<Property*>(sl)->buyHouse(current_player)){
                    cout << "Made it here" << endl;
                    if(dynamic_cast<Property*>(sl)->getHouses() == 1){
                        cout << "There is now 1 house on " << sl->getName() << "." << endl;
                    } else if(dynamic_cast<Property*>(sl)->getHouses() == 5){
                        cout << "There is now 1 hotel on " << sl->getName() << "." << endl;
                    } else {
                        cout << "There are now " << dynamic_cast<Property*>(sl)->getHouses() << " houses on " << sl->getName() << "." << endl;
                    }
                } else {
                    cout << "You cannot buy a house on this property." << endl;
                }

            }



            current_player->displayProperties();


        }

    }

    // Player bob("bob");
    // Player sandy("bob");
    // Location* myptr = &Baldwin;
    // Langsam.buyLocation(&bob);
    // MarketPointe.buyLocation(&bob);
    // myptr->buyLocation(&bob);
    // cout << "first rent: " << myptr->getRent() << endl;
    // cout << bob.getProperties().size() << endl;
    // dynamic_cast<Property*>(myptr)->buyHouse(&bob);
    // cout << "Houses: " << dynamic_cast<Property*>(myptr)->getHouses() << endl;
    // cout << "2nd rent: " << myptr->getRent() << endl;
    // dynamic_cast<Property*>(myptr)->buyHouse(&sandy);
    // cout << "Houses: " << dynamic_cast<Property*>(myptr)->getHouses() << endl;
    // cout << "3rd rent: " << myptr->getRent() << endl;
    // dynamic_cast<Property*>(myptr)->buyHouse(&bob);
    // cout << "Houses: " << dynamic_cast<Property*>(myptr)->getHouses() << endl;
    // cout << "4th rent: " << myptr->getRent() << endl;
    //
    // myptr->sellLocation(&bob);
    //
    // cout << bob.getProperties().size() << endl;



}
