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
    bool jailed, jail_pass;
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
    void setPos(int pos){position = pos;}
    int getMoney(){return money;}
    void addMoney(int amount){money += amount;}
    void subMoney(int amount){money -= amount;}
    bool inJail(){return jailed;}
    void switchJail(){jailed = !jailed;}
    bool getJailPass(){return jail_pass;}
    void switchJailPass(){jail_pass = !jail_pass;}
    void move(int amount){position = (position + amount) % 40;}
    bool canAfford(int price){return money - price > 0;}
    vector<Property> getProperties(){return properties;}
    vector<Eatery> getEateries(){return eateries;}
    vector<Street> getStreets(){return streets;}
    void addProperty(Property &new_property);
    void addEatery(Eatery &new_eatery);
    void addStreet(Street &new_street);
    void removeProperty(Property &property);
    void removeEatery(Eatery &eatery);
    void removeStreet(Street &street);
    void displayProperties();
};

class Location {
protected:
    int position, price, mortgage;
    string name, type;
    Player *owner;
public:
    Location(string lname, int lpos, int lprice, int lmort)
        : name(lname), position(lpos), price(lprice), mortgage(lmort)
    {
        owner = NULL;
    }

    int getPos(){return position;}
    int getPrice(){return price;}
    int getMortgage(){return mortgage;}
    string getName(){return name;}
    bool isOwned(){return owner;}
    string getOwner(){return owner->getName();}
    string getType(){return type;}
    virtual int getRent(){return 0;}
    virtual int getRent(int roll){return 0;}
    virtual void payRent(Player *rent_payer){
        int rent = getRent();
        rent_payer->subMoney(rent);
        owner->addMoney(rent);
    }
    virtual void payRent(Player *rent_payer, int roll){return;}
    void setOwner(Player *new_owner){owner = new_owner;}
    virtual bool buyLocation(Player *player){return 0;}
    virtual bool sellLocation(Player *player){return 0;}
};

class Property : public Location {
    int houses, house_price, rent0, rent1, rent2, rent3, rent4, rent5;
    string color;
public:
    Property(string lname, string lcolor, int lpos, int lprice, int lmort, int hprice, int r0, int r1, int r2, int r3, int r4, int r5)
        : Location(lname, lpos, lprice, lmort), color(lcolor), house_price(hprice),
          rent0(r0), rent1(r1), rent2(r2), rent3(r3), rent4(r4), rent5(r5)
    {
        houses = 0; type = "property";
    }
    bool buyLocation(Player *player){
        if(!player->canAfford(price) || owner) return false;
        player->subMoney(price);
        player->addProperty(*this);
        setOwner(player);
        return true;
    }
    bool sellLocation(Player *player){
        if(!(owner == player)) return false;
        owner->addMoney(mortgage);
        owner->removeProperty(*this);
        owner = NULL; houses = 0;
        return true;
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
    bool canBuyHouse(Player *player){
        if(player != owner || houses > 4) return false;
        int group_size = colorGroupSize(), count = 0;
        for(int i = 0; i < owner->getProperties().size(); i++){
            if(owner->getProperties()[i].getColor() == color) count++;
        }
        return (count == group_size && owner->canAfford(house_price));
    }
    bool buyHouse(Player *player){
        if(!canBuyHouse(player)) return false;
        houses++;
        owner->subMoney(house_price);
        return true;
    }
    bool sellHouse(int amount = 1){
        if(houses == 0 || amount > houses) return false;
        owner->addMoney(amount * house_price/2);
        houses -= amount;
        return true;
    }
    int getHouses(){return houses;}
};

class Eatery : public Location {
public:
    Eatery(string lname, int lpos, int lprice, int lmort)
        : Location(lname, lpos, lprice, lmort)
    {
        type = "eatery";
    }
    bool buyLocation(Player *player){
        if(!player->canAfford(price) || owner) return false;
        player->subMoney(price);
        player->addEatery(*this);
        setOwner(player);
        return true;
    }
    bool sellLocation(Player *player){
        if(!(owner == player)) return false;
        owner->addMoney(mortgage);
        owner->removeEatery(*this);
        owner = NULL;
        return true;
    }
    int getRent(int dice_roll){
        int count = 0;
        while(count < owner->getEateries().size()) count++;
        if(count == 1) return dice_roll * 4;
        return dice_roll * 10;
    }
    void payRent(Player *rent_payer, int dice_roll){
        int rent = getRent(dice_roll);
        rent_payer->subMoney(rent);
        owner->addMoney(rent);
    }
};

class Street : public Location {
public:
    Street(string lname, int lpos, int lprice, int lmort)
        : Location(lname, lpos, lprice, lmort)
    {
        type = "street";
    }
    bool buyLocation(Player *player){
        if(!player->canAfford(price) || owner) return false;
        player->subMoney(price);
        player->addStreet(*this);
        setOwner(player);
        return true;
    }
    bool sellLocation(Player *player){
        if(!(owner == player)) return false;
        owner->addMoney(mortgage);
        owner->removeStreet(*this);
        owner = NULL;
        return true;
    }
    int getRent(){
        int count = 0;
        while(count < owner->getStreets().size()) count++;
        return 25 * pow(2,count-1);
    }
};

class Other : public Location {
public:
    Other(string lname) : Location(lname, 0, 0, 0)
    {
        type = "other";
    }
};
