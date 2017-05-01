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
    cout << "\n\n\n"
         << "Welcome to the University of Cincinnati!!!" << endl
         << "It's time to play some..." << endl
         << "_________ BEARCATOPOLY _________" << "\n\n"
         << "Phase 1 - Player Creation" << endl;
    string player_name, input;
    int num_players = 0;
    while(num_players < 2 || num_players > 5){
        cout << "Enter the number of players (2-5): ";
        getline(cin, input);
        stringstream(input) >> num_players;
    }
    for(int i = 0; i < num_players; i++){
        cout << "Enter Player " << i+1 << "'s name: ";
        getline(cin, player_name);
        Player player_temp(player_name);
        PLAYERS.push_back(player_temp);
    }
    cout << endl << "Phase 2 - Game Play" << endl;
    int turn_count = 1, choice = 0, roll;
    Player *current_player;
    while(PLAYERS.size() > 1){
        for(int z = 0; z < PLAYERS.size(); z++){
            current_player = &PLAYERS[z];

            if(current_player->inJail() && current_player->getJailTime() < 3){
                cout << current_player->getName() << ", you're in jail." << endl;
                if(current_player->getJailPass()){
                    cout << "Use your Get Out of Jail Free pass? (y/n)" << endl;
                    getline(cin, input);
                    if(input != "y" && input != "yes" && input != "Yes") continue;
                    leaveJail(current_player);
                } else {
                    current_player->incJailTime();
                    continue;
                }
            } else if(current_player->inJail()) leaveJail(current_player);

            displayBoard();
            cout << "_____ Turn " << turn_count << " _____" << endl;
            cout << current_player->getName() << ", it's your turn. What would you like to do?" << endl;
            cout << "Your location: " << BOARD[current_player->getPos()]->getName() << endl;
            cout << "Your balance: $" << current_player->getMoney() << endl;
            current_player->displayProperties();

            while(choice != 1){
                choice = turnStartMenu();
                if(choice == 1){
                    roll = rollDice();
                    cout << "Your roll: " << roll << endl;

                    // cout << "Enter your roll: ";
                    // getline(cin, input);
                    // stringstream(input) >> roll;
                    current_player->move(roll);

                    Location *current_location = BOARD[current_player->getPos()];

                    if(current_location->getName() == "Bearcat Card"){
                        cout << "You landed on a Bearcat Card!" << endl;
                        cout << "The card says: ";
                        drawCard(current_player);
                        if(current_player->inJail()) break;
                        current_location = BOARD[current_player->getPos()];
                    } else {
                        cout << "You landed on " << current_location->getName() << "." << endl;
                    }
                    if(current_location->getType() != "other"){
                        if(current_location->isOwned()){
                            if(current_location->getOwner() == current_player->getName()){
                                cout << "You already own this property." << endl;
                            } else {
                                cout << current_location->getOwner() << " already owns this property. You'll have to pay rent." << endl;
                                if(current_location->getType() == "eatery"){
                                    current_location->payRent(current_player, roll);
                                    cout << "You paid $" << current_location->getRent(roll) << "." << endl;
                                } else {
                                    current_location->payRent(current_player);
                                    cout << "You paid $" << current_location->getRent() << "." << endl;
                                }
                            }
                        } else {
                            cout << "Nobody owns " << current_location->getName() << ". Would you like to buy it for $" << current_location->getPrice() << "? (y/n)" << endl;
                            getline(cin, input);
                            if(input == "y" || input == "yes" || input == "Yes"){
                                if(current_location->buyLocation(current_player)){
                                    cout << "Congratulations! You bought " << current_location->getName() << "!" << endl;
                                } else {
                                    cout << "You cannot buy " << current_location->getName() << "." << endl;
                                }
                            }
                        }
                    } else if(current_location->getName() == "Income Tax"){
                        int sum = 0;
                        for(int i = 0; i < current_player->getProperties().size(); i++) sum += current_player->getProperties()[i].getPrice();
                        for(int i = 0; i < current_player->getEateries().size(); i++) sum += current_player->getEateries()[i].getPrice();
                        for(int i = 0; i < current_player->getStreets().size(); i++) sum += current_player->getStreets()[i].getPrice();
                        cout << "Your total worth is $" << sum << "." << endl
                             << "So you paid $" << sum*0.1 << " in taxes." << endl;
                        current_player->subMoney(sum*0.1);
                    } else if(current_location->getName() == "Luxury Tax"){
                        cout << "You paid a luxury tax of $100." << endl;
                        current_player->subMoney(100);
                    } else if(current_location->getName() == "Go To Jail"){
                        cout << "You went to jail." << endl;
                        current_player->setPos(420);
                        current_player->switchJail();
                        break;
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
                    } else {
                        cout << "Sell " << selected_location->getName() << " for $" << selected_location->getMortgage() << "? (y/n)" << endl;
                        getline(cin, input);
                        if(input == "y" || input == "yes" || input == "Yes"){
                            if(selected_location->sellLocation(current_player)){
                                cout << "You sold " << selected_location->getName() << " for $" << selected_location->getMortgage() << "." << endl;
                            } else {
                                cout << "You cannot sell a property that you do not own." << endl;
                            }
                        }
                    }
                } else if(choice == 4){
                    cout << "Enter the name of the property where you'd like to build houses: ";
                    string property_name; Location *sl = NULL;
                    getline(cin, property_name);
                    for(int i = 0; i < 40; i++){
                        if(BOARD[i]->getName() == property_name && BOARD[i]->getType() == "property") sl = BOARD[i];
                    }
                    if(!sl){
                        cout << "You did not enter a valid property name." << endl;
                    } else {
                        cout << "Build a house on " << sl->getName() << " for $" << dynamic_cast<Property*>(sl)->getHousePrice() << "? (y/n)" << endl;
                        getline(cin, input);
                        if(input == "y" || input == "yes" || input == "Yes"){
                            if(dynamic_cast<Property*>(sl)->buyHouse(current_player)){
                                cout << "You built a house on " << sl->getName() << " for $" << dynamic_cast<Property*>(sl)->getHousePrice() << "." << endl;
                                if(dynamic_cast<Property*>(sl)->getHouses() == 1){
                                    cout << "There is now 1 house on " << sl->getName() << "." << endl;
                                } else if(dynamic_cast<Property*>(sl)->getHouses() == 5){
                                    cout << "There is now 1 hotel on " << sl->getName() << "." << endl;
                                } else {
                                    cout << "There are now " << dynamic_cast<Property*>(sl)->getHouses() << " houses on " << sl->getName() << "." << endl;
                                }
                            } else {
                                cout << "You cannot build a house on this property." << endl;
                            }
                        }
                    }
                } else if(choice == 5){
                    cout << "Enter the name of the property where you'd like to sell houses: ";
                    string property_name; Location *sl = NULL;
                    getline(cin, property_name);
                    for(int i = 0; i < 40; i++){
                        if(BOARD[i]->getName() == property_name && BOARD[i]->getType() == "property") sl = BOARD[i];
                    }
                    if(!sl){
                        cout << "You did not enter a valid property name." << endl;
                    } else {
                        cout << "Sell a house on " << sl->getName() << " for $" << dynamic_cast<Property*>(sl)->getHousePrice() << "? (y/n)" << endl;
                        getline(cin, input);
                        if(input == "y" || input == "yes" || input == "Yes"){
                            if(dynamic_cast<Property*>(sl)->sellHouse(current_player)){
                                cout << "You sold 1 house on " << sl->getName() << " for $" << dynamic_cast<Property*>(sl)->getHousePrice() << "." << endl;
                                if(dynamic_cast<Property*>(sl)->getHouses() == 1){
                                    cout << "There is now 1 house on " << sl->getName() << "." << endl;
                                } else if(dynamic_cast<Property*>(sl)->getHouses() == 5){
                                    cout << "There is now 1 hotel on " << sl->getName() << "." << endl;
                                } else {
                                    cout << "There are now " << dynamic_cast<Property*>(sl)->getHouses() << " houses on " << sl->getName() << "." << endl;
                                }
                            } else {
                                cout << "You cannot sell a house on this property." << endl;
                            }
                        }
                    }
                }
            }
                choice = 0;
                cout << "Your balance: $" << current_player->getMoney() << endl;
                cout << current_player->getName() << ", press enter when you're ready to end your turn.";
                getline(cin,input);
        }

        for(int i = 0; i < PLAYERS.size(); i++){
            if(PLAYERS[i].getMoney() < 0){
                cout << endl
                     << PLAYERS[i].getName() << ", you have been eliminated. Thank you for playing." << endl;
                PLAYERS.erase(PLAYERS.begin()+i);
            }
        }
        turn_count++;
    }
    cout << endl << "Phase 3 - Victory" << endl
         << "Congratulations, " << PLAYERS[0].getName() << ". You won Bearcatopoly." << endl
         << "Now let us celebrate in song...\n\n"
         << "O Cincinnati, magic name, I proudly to the world proclaim;\n"
         << "No sweeter word ever charmed my ear,\n"
         << "None to my heart was ever so dear,\n"
         << "A fountain of eternal youth, a tower of strength, a rock of truth.\n\n"
         << "Oh varsity, dear varsity, thy loyal children we will be,\n"
         << "Thy loyal, loyal children we will be.\n\n"
         << "Of wealth and station some may boast, of wide renown from coast to coast;\n"
         << "None nobler teachings did instill,\n"
         << "Than old McMicken on the hill,\n"
         << "The black and red banner floats on high, let all join in the battle cry.\n\n"
         << "Oh varsity, dear varsity, thy loyal children we will be,\n"
         << "Thy loyal, loyal children we will be.\n\n"
         << "Long may she live, her children's pride, and grow and prosper far and wide.\n"
         << "At all time let our motto be: stand first and last for old UC,\n"
         << "We dedicate with might and main, to Alma Mater this refrain:\n\n"
         << "Oh varsity, dear varsity, thy loyal children we will be,\n"
         << "Thy loyal, loyal children we will be.\n";

}
