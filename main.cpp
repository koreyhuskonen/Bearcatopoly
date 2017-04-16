#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include "Monopoly.cpp"


using namespace std;

int main(){
    int num_players;
    cout << "Enter how many players: ";
    cin >> num_players;
    cout << "_____ Create Players _____" << endl;
    for(int i = 1; i <= num_players; i++){
        string name;
        cout << "Enter Player" + to_string(i) + "'s name: ";
        cin >> name;
        Player temp(name);
        PLAYERS.push_back(temp);
    }

    for(int i = 0; i < num_players; i++){
        cout << "Player" + to_string(i+1) + ": ";
        cout << PLAYERS[i].name << endl;
    }

    return 0;
}
