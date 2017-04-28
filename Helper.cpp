#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

string mystr;

int turnStartMenu(Player *player){
    int choice;
    cout << player->getName() << ", it's your turn. What would you like to do?" << endl
         << "Options:" << endl
         << "1. Roll to move" << endl
         << "2. Sell some of your properties" << endl
         << "3. Build houses on your properties" << endl;
    do {
        cout << "Enter your choice: ";
        getline(cin, mystr);
        stringstream(mystr) >> choice;
    } while(choice < 1 || choice > 3);
    cout << endl;
    return choice;
}





int rollDice(){
    int roll_1, roll_2, move;
    srand(time(NULL));
    roll_1 = rand() % 6 + 1;
    roll_2 = rand() % 6 + 1;
    move = roll_1 + roll_2;
    if(roll_1 == roll_2){
    // TODO: Fill this in
    }
    return move;
}


int getRandomCard(){
    srand(time(NULL));
    int card_number = rand() % 12;
    return card_number;
}


void drawCard(Player &player){
    int card_number = getRandomCard();
    if(card_number == 0){
    // Advance to Go. Collect $200.
        player.setPos(0);
        player.addMoney(200);
    }
    else if(card_number == 1){
    // Get out of Jail Free
        if(player.getJailPass() == true) player.addMoney(50);
        if(player.getJailPass() == false) player.switchJailPass();
    }
    else if(card_number == 2){
    // You got caught on Bearcat Snaps. Go directly to Jail. Do not pass Go. Do not collect $200.
        player.setPos(420);
        player.switchJail();
    }
    else if(card_number == 3){
    // You joined Greek Life!!! Pay your dues. (Pay $100)
        player.subMoney(100);
    }
    else if(card_number == 4){
    // It's your birthday!!! Collect $10 from every player.
        for(int i = 0; i < PLAYERS.size(); i++){
            PLAYERS[i].subMoney(10);
            player.addMoney(10);
        }
    }
    else if(card_number == 5){
    // You missed out on Tender Tuesday. Advance to Raising Cane's to get some tenders.
        if(player.getPos() > 28) player.addMoney(200);
        player.setPos(28);
    }
    else if(card_number == 6){
    // You and your roommates need a snack while studying. Advance to Insomnia Cookies.
        if(player.getPos() > 12) player.addMoney(200);
        player.setPos(12);
    }
    else if(card_number == 7){
    // UC has construction on campus. Move back 3 spaces.
        int current_position = player.getPos();
        player.setPos(current_position - 3);
    }
    else if(card_number == 8){
    // You won a scholarship contest. (Collect $150)
        player.addMoney(150);
    }
    else if(card_number == 9){
    // The college basketball season has begun. You purchase a UC basketball season ticket. (Pay $50)
        player.subMoney(50);
    }
    else if(card_number == 10){
    // You spotted the Bearcat on campus. (Collect $50)
        player.addMoney(50);
    }
    else {
    // Pay your respects to Harambe. (Pay $100)
        player.subMoney(100);
    }
}
