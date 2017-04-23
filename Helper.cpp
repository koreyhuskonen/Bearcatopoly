#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

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


// void drawCard(Player &player){
//     int card_number = getRandomCard();
//     if(card_number == 0){
//         // Advance to Go. Collect $200
//         player.setPos(0);
//         player.addMoney(200);
//     }
//     else if(card_number == 1){
//         // Get out of Jail Free Pass
//         if(player.getJailPass() == true) player.addMoney(50);
//         if(player.getJailPass() == false) player.switchJailPass();
//     }
//     else if(card_number == 2){
//         // You got caught on Bearcat Snaps. Go directly to jail, Do not pass Go, do not collect $200
//         player.getPos() = 420;
//         player.in_jail() = true;
//     }
//     else if(card_number == 3){
//     You joined Greek Life!!! Pay your dues. (Pay $100)
//     }
//     else if(card_number == 4){
//     Its your birthday!!! Collect $10 from every player
//     }
//     else if(card_number == 5){
//     You missed out on Tender Tuesday. Advance to Raising Cane's to get some Tenders.
//     }
//     else if(card_number == 6){
//     You and your roommates are in need of a snack while studying. Advance to Insomnia Cookies.
//     }
//     else if(card_number == 7){
//     UC has construction on campus. Move back 3 spaces.
//     }
//     else if(card_number == 8){
//     You won a scholarship contest. (Collect $150)
//     }
//     else if(card_number == 9){
//     The college basketball season has began. You purchase a UC basketball season ticket. (Pay $50)
//     }
//     else if(card_number == 10){
//     You spotted Bearcat on campus. (collect $50)
//     }
//     else Pay your respects to Harambe. (Pay $50)
//
// }
