#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

int turnStartMenu(){
    int choice; string mystr;
    cout << endl << "Options:" << endl
         << "1. Roll to move" << endl
         << "2. Display your properties" << endl
         << "3. Sell some of your properties" << endl
         << "4. Build houses on your properties" << endl
         << "5. Sell houses on your properties" << endl;
    do {
        cout << "Enter your choice: ";
        getline(cin, mystr);
        stringstream(mystr) >> choice;
    } while(choice < 1 || choice > 5);
    return choice;
}

void leaveJail(Player *player){
    player->resetJailTime();
    player->switchJail();
    player->setPos(10);
    cout << player->getName() << ", you got out of jail." << endl;
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
            cout << "But you already had one, so you sold the new pass for $50." << endl;
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
        cout << "You missed out on Chicken Tender Tuesday. Advance to Raising Cane's to get some tenders." << endl;
        if(player->getPos() > 28){
            cout << "You passed Go! Collect $200." << endl;
            player->addMoney(200);
        }
        player->setPos(28);
    }
    else if(card_number == 6){
        cout << "You and your roommates need a snack while studying. Advance to Insomnia Cookies." << endl;
        if(player->getPos() > 12){
            cout << "You passed Go! Collect $200." << endl;
            player->addMoney(200);
        }
        player->setPos(12);
    }
    else if(card_number == 7){
        cout << "There's construction on campus. Move back 3 spaces." << endl;
        int current_position = player->getPos();
        player->setPos(current_position - 3);
        if(player->getPos() < 0) player->setPos(39);
        if(BOARD[player->getPos()]->getName() == "Bearcat Card"){
            cout << "You landed on another Bearcat Card!" << endl;
            cout << "The card says: ";
            drawCard(player);
        }
    }
    else if(card_number == 8){
        cout << "You won a scholarship contest. (Collect $150)" << endl;
        player->addMoney(150);
    }
    else if(card_number == 9){
        cout << "You purchased a UC basketball season ticket. (Pay $50)" << endl;
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

void displayBoard(){
    cout << " __________________________________________________________________________________________________________________________________________________ " << endl;
    cout << "|   Free       |   Turner   |  Bearcat   |  Teachers  |            |            |            |   Fifth    |  Raising   |   Sigma    |    Go To     |" << endl;
    cout << "|   Parking    |   Hall     |  Card      |  College   |    UPA     |   MLK Dr   |    ERC     |   Third    |  Cane's    |   Sigma    |    Jail      |" << endl;
    cout << "|______________|____________|____________|____________|____________|____________|____________|____________|____________|____________|______________|" << endl;
    cout << "|              |                                                                                                                    |   McMicken   |" << endl;
    cout << "|  Rec Center  |                                                                                                                    |   Hall       |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|              |                                                                                                                    |   Nippert    |" << endl;
    cout << "|     DAAP     |                                                                                                                    |   Stadium    |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|   Bearcat    |                                                                                                                    |   Bearcat    |" << endl;
    cout << "|   Card       |                                                                                                                    |   Card       |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|   Lindner    |                                                                                                                    |              |" << endl;
    cout << "|   College    |                                                                                                                    |     TUC      |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|              |                                                                                                                    |   Jefferson  |" << endl;
    cout << "| Clifton Ave  |                                                                                                                    |   Ave        |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|              |                                                                                                                    |   Bearcat    |" << endl;
    cout << "| MarketPointe |                                                                                                                    |   Card       |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|   Langsam    |                                                                                                                    |              |" << endl;
    cout << "|   Library    |                                                                                                                    |   Morgens    |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|   Insomnia   |                                                                                                                    |   Luxury     |" << endl;
    cout << "|   Cookies    |                                                                                                                    |   Tax        |" << endl;
    cout << "|______________|                                                                                                                    |______________|" << endl;
    cout << "|   Baldwin    |                                                                                                                    |              |" << endl;
    cout << "|   Hall       |                                                                                                                    |   Scioto     |" << endl;
    cout << "|______________|____________________________________________________________________________________________________________________|______________|" << endl;
    cout << "|              |            |            |            |            |            |            |            |            |            |              |" << endl;
    cout << "|     Jail     |  Crosley   |   Center   |  Bearcat   |  Calhoun   |  Calhoun   |   Income   |  Old Chem  |  Bearcat   |   Dabney   |      Go      |" << endl;
    cout << "|              |  Tower     |   Court    |  Card      |  Hall      |  St        |   Tax      |            |  Card      |   Hall     |              |" << endl;
    cout << " -------------------------------------------------------------------------------------------------------------------------------------------------- " << endl;
}
