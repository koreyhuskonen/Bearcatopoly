#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include "Monopoly.h"

using namespace std;

vector<Player> PLAYERS;

// p_name, p_color, pos, p_price, p_mort, h_price, r0, r1, r2, r3, r4, r5
Property Dabney("Dabney Hall", "brown", 1, 60, 30, 50, 2, 10, 30, 90, 160, 250);
Property Old_Chem("Old Chem", "brown", 3, 60, 30, 50, 4, 20, 60, 180, 320, 450);
Property Calhoun("Calhoun Hall", "light blue", 6, 100, 50, 50, 6, 30, 90, 270, 400, 550);
Property Center_Court("Center Court", "light blue", 8, 100, 50, 50, 6, 30, 90, 270, 400, 550);
Property Crosley_Tower("Crosley Tower", "light blue", 9, 120, 60, 50, 8, 40, 100, 300, 450, 600);
Property Baldwin("Baldwin Hall", "pink", 11, 140, 70, 100, 10, 50, 150, 450, 625, 750);
Property Langsam("Langsam Library", "pink", 13, 140, 70, 100, 10, 50, 150, 450, 625, 750);
Property MarketPointe("MarketPointe", "pink", 14, 160, 80, 100, 12, 60, 180, 500, 700, 900);
Property Lindner("Lindner College", "orange", 16, 180, 90, 100, 14, 70, 200, 550, 750, 950);
Property DAAP("DAAP", "orange", 18, 180, 90, 100, 14, 70, 200, 550, 750, 950);
Property Rec_Center("Rec Center", "orange", 19, 200, 100, 100, 16, 80, 220, 600, 800, 1000);
Property Turner("Turner Hall", "red", 21, 220, 110, 150, 18, 90, 250, 700, 875, 1050);
Property Teachers("Teachers College", "red", 23, 220, 110, 150, 18, 90, 250, 700, 875, 1050);
Property UPA("UPA", "red", 24, 240, 120, 150, 20, 100, 300, 750, 925, 1100);
Property ERC("ERC", "yellow", 26, 260, 130, 150, 22, 110, 330, 800, 975, 1150);
Property Fifth_Third("Fifth Third", "yellow", 27, 260, 130, 150, 22, 110, 330, 800, 975, 1150);
Property Sigma("Sigma Sigma", "yellow", 29, 280, 140, 150, 24, 120, 360, 850, 1025, 1200);
Property McMicken("McMicken Hall", "green", 31, 300, 150, 200, 26, 130, 390, 900, 1100, 1275);
Property Nippert("Nippert Stadium", "green", 32, 300, 150, 200, 26, 130, 390, 900, 1100, 1275);
Property TUC("TUC", "green", 34, 320, 160, 200, 28, 150, 450, 1000, 1200, 1400);
Property Morgens("Morgens", "dark blue", 37, 350, 175, 200, 35, 175, 500, 1100, 1300, 1500);
Property Scioto("Scioto", "dark blue", 39, 400, 200, 200, 50, 200, 600, 1400, 1700, 2000);

Eatery Canes("Raising Cane's", 28, 150, 75);
Eatery Insomnia("Insomnia Cookies", 12, 150, 75);

Street Calhoun_St("Calhoun St", 5, 200, 100);
Street Clifton_Ave("Clifton Ave", 15, 200, 100);
Street MLK_Dr("MLK Dr", 25, 200, 100);
Street Jefferson_Ave("Jefferson Ave", 35, 200, 100);

Other card1("Bearcat Card"), card2("Bearcat Card"), card3("Bearcat Card"),
      card4("Bearcat Card"), card5("Bearcat Card"), card6("Bearcat Card"),
      tax1("Income Tax"), tax2("Luxury Tax"),
      Go("Go"), VisitingJail("Visiting Jail"),
      FreeParking("Free Parking"), GoToJail("Go To Jail");

Location* BOARD[] = {&Go, &Dabney, &card1, &Old_Chem, &tax1, &Calhoun_St, &Calhoun,
                     &card2, &Center_Court, &Crosley_Tower, &VisitingJail, &Baldwin,
                     &Insomnia, &Langsam, &MarketPointe, &Clifton_Ave, &Lindner,
                     &card3, &DAAP, &Rec_Center, &FreeParking, &Turner, &card4, &Teachers,
                     &UPA, &MLK_Dr, &ERC, &Fifth_Third, &Canes, &Sigma, &GoToJail,
                     &McMicken, &Nippert, &card5, &TUC, &Jefferson_Ave, &card6,
                     &Morgens, &tax2, &Scioto};

void Player::addProperty(Property &new_property){properties.push_back(new_property);}
void Player::addEatery(Eatery &new_eatery){eateries.push_back(new_eatery);}
void Player::addStreet(Street &new_street){streets.push_back(new_street);}
void Player::removeProperty(Property &property){
    int i = 0;
    while(properties[i].getName() != property.getName()) i++;
    properties.erase(properties.begin()+i);
}
void Player::removeEatery(Eatery &eatery){
    int i = 0;
    while(eatery.getName() != eateries[i].getName()) i++;
    eateries.erase(eateries.begin()+i);
}
void Player::removeStreet(Street &street){
    int i = 0;
    while(street.getName() != streets[i].getName()) i++;
    streets.erase(streets.begin()+i);
}
void Player::displayProperties(){
    cout << name << "'s Properties: ";
    for(int i = 0; i < properties.size(); i++) cout << properties[i].getName() << "  ";
    for(int i = 0; i < eateries.size(); i++) cout << eateries[i].getName() << "  ";
    for(int i = 0; i < streets.size(); i++) cout << streets[i].getName() << "  ";
    cout << endl;
}
