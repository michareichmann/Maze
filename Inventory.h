#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>

class Items
{
private:
    string _itemName;
    ushort _quantity;

public:
    Items(string sName, ushort nNumber): _itemName(sName), _quantity(nNumber) {}

    /**getters*/
    string name() {return _itemName;}
    ushort count(){return _quantity;}

    /**setters*/
    void set(ushort nNumber) { _quantity = nNumber;}
    void decrease() {_quantity -= 1;}
    void increase() {_quantity += 1;}

};

class Inventory
{
private:
    vector<Items> _inventory;
    ushort _nItems;

public:

    Inventory(): _nItems(0) {}
    Inventory(Items first) {
    _inventory.resize(1,first);
    _nItems = _inventory.size();
    }

    /**getters*/
    string name(ushort index)   {return _inventory[index].name();}
    ushort count(ushort index)  {return _inventory[index].count();}
    ushort size()               {return _nItems;}
    ushort count(string sItemName) {for (ushort i(0); i<_nItems; i++){ if (_inventory[i].name()==sItemName) {return _inventory[i].count(); break;}}}


    /**setters*/
    void addItem(string sName, ushort quantity){
    _inventory.push_back(Items(sName,quantity));
    _nItems = _inventory.size();
    }

    void increase(string sItemName) {for (ushort i(0); i<_nItems; i++){ if (_inventory[i].name()==sItemName) {_inventory[i].increase(); break;}}}
    void decrease(string sItemName) {for (ushort i(0); i<_nItems; i++){ if (_inventory[i].name()==sItemName) {_inventory[i].decrease(); break;}}}

    /**output*/
    friend ostream & operator<<(ostream & os, Inventory & c1) {
        os << "INVENTORY:\n\n";
        if  (!c1.size()) os << "You got nothing...\n";
        for (ushort i(0); i<c1.size(); i++){
            os << c1.name(i) <<(c1.name(i)=="Match" ? "e" : "") << ((c1.count(i)>1) ? "s" : "");
            os << "\t\t: " << c1.count(i) << "\t";
            if ((i+1)%2==0) os << "\n";
        }
        os << "\n";
        return os;
    }
};

#endif // INVENTORY_H
