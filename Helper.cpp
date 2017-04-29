#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

int turnStartMenu(Player *player){
    int choice; string mystr;
    cout << player->getName() << ", it's your turn. What would you like to do?" << endl
         << "Options:" << endl
         << "1. Roll to move" << endl
         << "2. Display your properties" << endl
         << "3. Sell some of your properties" << endl
         << "4. Build houses on your properties" << endl;
    do {
        cout << "Enter your choice: ";
        getline(cin, mystr);
        stringstream(mystr) >> choice;
    } while(choice < 1 || choice > 4);
    return choice;
}

void leaveJail(Player *player){
    player->resetJailTime();
    player->switchJail();
    player->setPos(10);
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


void drawCard(Player *player){
    int card_number = getRandomCard();
    if(card_number == 0){
        cout << "Advance to Go. Collect $200." << endl;
        player->setPos(0);
        player->addMoney(200);
    }
    else if(card_number == 1){
        cout << "You acquired a Get Out of Jail Free Pass." << endl;
        if(player->getJailPass() == true){
            cout << "But you can only have one pass at a time, so you sold the new pass for $50." << endl;
            player->addMoney(50);
        }
        if(player->getJailPass() == false) player->switchJailPass();
    }
    else if(card_number == 2){
        cout << "Caught on Bearcat Snaps!!! Go directly to Jail. Do not pass Go. Do not collect $200." << endl;
        player->setPos(420);
        player->switchJail();
    }
    else if(card_number == 3){
        cout << "You joined Greek Life!!! Pay your dues. (Pay $100)" << endl;
        player->subMoney(100);
    }
    else if(card_number == 4){
        cout << "It's your birthday!!! Collect $10 from every player." << endl;
        for(int i = 0; i < PLAYERS.size(); i++){
            PLAYERS[i].subMoney(10);
            player->addMoney(10);
        }
    }
    else if(card_number == 5){
        cout << "You missed out on Tender Tuesday. Advance to Raising Cane's to get some tenders." << endl;
        if(player->getPos() > 28) player->addMoney(200);
        player->setPos(28);
    }
    else if(card_number == 6){
        cout << "You and your roommates need a snack while studying. Advance to Insomnia Cookies." << endl;
        if(player->getPos() > 12) player->addMoney(200);
        player->setPos(12);
    }
    else if(card_number == 7){
        cout << "There's construction on campus. Move back 3 spaces." << endl;
        int current_position = player->getPos();
        player->setPos(current_position - 3);
        if(player->getPos() < 0) player->setPos(39);
    }
    else if(card_number == 8){
        cout << "You won a scholarship contest. (Collect $150)" << endl;
        player->addMoney(150);
    }
    else if(card_number == 9){
        cout << "The college basketball season has begun. You purchase a UC basketball season ticket. (Pay $50)" << endl;
        player->subMoney(50);
    }
    else if(card_number == 10){
        cout << "You spotted the Bearcat on campus. (Collect $50)" << endl;
        player->addMoney(50);
    }
    else {
        cout << "Pay your respects to Harambe. (Pay $100)" << endl;
        player->subMoney(100);
    }
}
