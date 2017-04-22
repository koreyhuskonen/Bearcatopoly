#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Location;
class Property;
class Eatery;
class Street;

class Player {
    string name;
    int position, money;
    bool jailed;
    vector<Property> properties;
    vector<Eatery> eateries;
    vector<Street> streets;
public:
    Player(string player_name){
        name = player_name;
        position = 0;
        money = 1500;
        jailed = false;
    }
    string getName(){return name;}
    int getPos(){return position;}
    int getMoney(){return money;}
    void addMoney(int amount){money += amount;}
    void subMoney(int amount){money -= amount;}
    bool in_jail(){return jailed;}
    void move(int amount){position = (position + amount) % 40;}
    vector<Property> getProperties(){return properties;}
    vector<Eatery> getEateries(){return eateries;}
    vector<Street> getStreets(){return streets;}
    bool canAfford(int price){return money - price > 0;}
};

class Location {
protected:
    int position, price, mortgage;
    string name;
    bool owned;
    Player *owner;
public:
    Location(string lname, int lpos, int lprice, int lmort)
        : name(lname), position(lpos), price(lprice), mortgage(lmort)
    {
        owned = false; owner = NULL;
    }

    int getPos(){return position;}
    int getPrice(){return price;}
    int getMortgage(){return mortgage;}
    string getName(){return name;}
    bool is_owned(){return owned;}
    string getOwner(){return owner->getName();}
    virtual int getRent(){return 0;}
    virtual void pay_rent(Player &rent_payer){
        int rent = getRent();
        rent_payer.subMoney(rent);
        owner->addMoney(rent);
    }
    void change_owner(Player *new_owner){owner = new_owner;}
    bool buy_location(Player *player){
        if(!player->canAfford(price)) return false;
        player->subMoney(price);
        change_owner(player);
        return true;
    }
};

class Property : public Location {
    int houses, house_price, rent0, rent1, rent2, rent3, rent4, rent5;
    string color;
public:
    Property(string lname, string lcolor, int lpos, int lprice, int lmort, int hprice, int r0, int r1, int r2, int r3, int r4, int r5)
        : Location(lname, lpos, lprice, lmort), color(lcolor), house_price(hprice),
          rent0(r0), rent1(r1), rent2(r2), rent3(r3), rent4(r4), rent5(r5)
    {
        houses = 0;
    }

    string getColor(){return color;}
    int getRent(){
        if(houses == 0) return rent0;
        if(houses == 1) return rent1;
        if(houses == 2) return rent2;
        if(houses == 3) return rent3;
        if(houses == 4) return rent4;
        return rent5;
    }
    int colorGroupSize(){
        if (color == "brown" || color == "dark blue") return 2;
        return 3;
    }
    bool canBuyHouse(Player &player){
        int group_size = colorGroupSize(), count;
        for(int i = 0; i < player.getProperties().size(); i++){
            if(player.getProperties()[i].getColor() == color) count++;
        }
        return (count == group_size && player.canAfford(house_price) && houses <= 5);
    }
    bool buy_house(Player &player){
        if(!canBuyHouse(player)) return false;
        houses++;
        player.subMoney(house_price);
        return true;
    }
};

class Eatery : public Location {
public:
    Eatery(string lname, int lpos, int lprice, int lmort)
        : Location(lname, lpos, lprice, lmort) {}

    int getRent(int dice_roll){
        int count = 0;
        while(count < owner->getEateries().size()) count++;
        if(count == 1) return dice_roll * 4;
        return dice_roll * 10;
    }
    void pay_rent(Player &rent_payer, int dice_roll){
        int rent = getRent(dice_roll);
        rent_payer.subMoney(rent);
        owner->addMoney(rent);
    }
};

class Street : public Location {
public:
    Street(string lname, int lpos, int lprice, int lmort)
        : Location(lname, lpos, lprice, lmort) {}

    int getRent(){
        int count = 0;
        while(count < owner->getStreets().size()) count++;
        return 25 * pow(2,count-1);
    }
};
