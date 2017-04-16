#include <string>

using namespace std;

class Player {
public:
    string name;
    double money;
    int position;
    bool in_jail;

    Player(string st){
        name = st;
        money = 1500;
        position = 0;
        in_jail = false;
    }

};

class Property {
    int position, price, houses, hotels, house_price, hotel_price, rent, mortgage;
    string name, color;
    bool owned;
    Player owner;

    Property(string prop_name, string prop_color, int prop_cost, int prop_rent, int prop_mort, int house_cost, int hotel_cost){
        position = 0; houses = 0; hotels = 0; owned = false;
        name = prop_name;
        color = prop_color;
        price = prop_cost;
        rent = prop_rent;
        mortgage = prop_mort;
        house_price = house_cost;
        hotel_price = hotel_cost;
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
