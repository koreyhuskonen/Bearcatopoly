#include <string>

using namespace std;

class Player {
    string name;
    double money;
    int position;
    bool jailed;
public:
    Player(string player_name){
        name = player_name;
        money = 1500;
        position = 0;
        jailed = false;
    }
    string getName(){return name;}
    double getMoney(){return money;}
    void addMoney(int amount){money += amount;}
    void subMoney(int amount){money -= amount;}
    int getPos(){return position;}
    void move(int roll){position = (position + roll) % 40;}
    bool in_jail(){return jailed;}
};

class Property {
    int position, price, houses, house_price, mortgage, rent0, rent1, rent2, rent3, rent4, rent5;
    string name, color;
    bool owned;
    Player *owner;
public:
    Property(string p_name, string p_color, int pos, int p_price, int p_mort, int h_price, int r0, int r1, int r2, int r3, int r4, int r5){
        name = p_name;
        color = p_color;
        position = pos;
        price = p_price;
        mortgage = p_mort;
        house_price = h_price;
        rent0 = r0; rent1 = r1; rent2 = r2; rent3 = r3; rent4 = r4; rent5 = r5;
        houses = 0; owned = false; owner = NULL;
    }
    int getPos(){return position;}
    int getPrice(){return price;}
    int getHouses(){return houses;}
    int getHousePrice(){return house_price;}
    int getMortgage(){return mortgage;}
    string getName(){return name;}
    string getColor(){return color;}
    bool is_owned(){return owned;}
    string getOwner(){return owner->getName();}
    int getRent(){
        switch(houses){
            case 0:
                return rent0;
            case 1:
                return rent1;
            case 2:
                return rent2;
            case 3:
                return rent3;
            case 4:
                return rent4;
            case 5:
                return rent5;
            default:
                return rent0;
        }
    }
    void pay_rent(Player rent_payer){
        int rent = getRent();
        rent_payer.subMoney(rent);
        owner->addMoney(rent);
    }
};

class Utility {
    int position;
    string name;
    int price;
    bool owned;
    Player owner;

    bool check_ownership(Utility other_utility);
    void pay_rent(Player rent_payer);
};

class Card {
    int position;

    void draw_card(Player current_player);
};
