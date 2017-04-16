#include <string>

using namespace std;

class Player {
    string name;
    double money;
    int position;
    bool jailed;
public:
    Player(string st){
        name = st;
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
    int position, price, houses, house_price, rent, mortgage;
    string name, color;
    bool owned;
    Player *owner;
public:
    Property(string prop_name, string prop_color, int pos, int prop_price, int prop_rent, int prop_mort, int house_cost){
        houses = 0; owned = false;
        name = prop_name;
        color = prop_color;
        position = pos;
        price = prop_price;
        rent = prop_rent;
        mortgage = prop_mort;
        house_price = house_cost;
        owner = NULL;
    }

    void pay_rent(Player rent_payer);
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
