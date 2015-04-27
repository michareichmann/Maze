#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>

class Items
{
private:
    string _itemName;
    uint16_t _quantity;

public:
    Items(string sName, uint16_t nNumber): _itemName(sName), _quantity(nNumber) {}

    /**getters*/
    string name() {return _itemName;}
    uint16_t count(){return _quantity;}

    /**setters*/
    void set(uint16_t nNumber) { _quantity = nNumber;}
    void decrease() {_quantity -= 1;}
    void increase() {_quantity += 1;}

};

class Inventory
{
private:
    vector<Items> _inventory;
    uint16_t _nItems;

public:

    Inventory(): _nItems(0) {}
    Inventory(Items first) {
    _inventory.resize(1,first);
    _nItems = _inventory.size();
    }

    /**getters*/
    string name(uint16_t index)   {return _inventory[index].name();}
    uint16_t count(uint16_t index)  {return _inventory[index].count();}
    uint16_t size()               {return _nItems;}
    uint16_t count(string sItemName) {
        uint16_t countItem;
        for (uint16_t i(0); i<_nItems; i++) {
            if (_inventory[i].name()==sItemName) {countItem = _inventory[i].count(); break;}
        }
        return countItem;
    }


    /**setters*/
    void addItem(string sName, uint16_t quantity){
    _inventory.push_back(Items(sName,quantity));
    _nItems = _inventory.size();
    }

    void increase(string sItemName) {for (uint16_t i(0); i<_nItems; i++){ if (_inventory[i].name()==sItemName) {_inventory[i].increase(); break;}}}
    void decrease(string sItemName) {for (uint16_t i(0); i<_nItems; i++){ if (_inventory[i].name()==sItemName) {_inventory[i].decrease(); break;}}}

    /**output*/
    friend ostream & operator<<(ostream & os, Inventory & c1) {
        os << "INVENTORY:\n\n";
        if  (!c1.size()) os << "You got nothing...\n";
        for (uint16_t i(0); i<c1.size(); i++){
            os << c1.name(i) <<(c1.name(i)=="Match" ? "e" : "") << ((c1.count(i)>1) ? "s" : "");    /**exeptions for plural*/
            if (c1.name(i).size() < 8) os << "\t\t";                                                /**check length for tabs*/
            else os << "\t";
            os << "\t: " << c1.count(i) << "\t";
            if ((i+1)%2==0) os << "\n";
        }
        os << "\n";
        return os;
    }
};

#endif // INVENTORY_H
