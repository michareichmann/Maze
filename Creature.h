#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include "Point.h"
#include "Inventory.h"
#include "Setup.h"
#include <unistd.h>
#include <stdio.h>


using namespace std;

class Creature
{
private:
    string m_sName;
    Point m_Location;
    Inventory _inventory;

    Creature() { }

public:
    Creature(string sName, const Point & cLocation, const Inventory & cInventory): m_sName(sName), m_Location(cLocation), _inventory(cInventory) { }

    /** getter function for the positon*/
    ushort x() {return m_Location.x();}
    ushort y() {return m_Location.y();}
    ushort count(string sItemName) {for (ushort i(0); i<_inventory.size(); i++){ if (_inventory.name(i)==sItemName) {return _inventory.count(i); break;}}}

    friend ostream & operator<<(ostream & os, Creature & c1)
    {
        os << c1.m_sName << " is at " << c1.m_Location;
        return os;
    }

    /** setter functions*/

    void createInventory();

    /** actions of the creature*/
    void moveTo(cushort & col, cushort & row, const char & dir, Matrix<char> & maze);

    void position() {cout << m_sName << " is at " << m_Location << endl;}

    void lookMap(Matrix<char> & maze, Matrix<char> & emptyMaze);

    void breakWall(Matrix<char> & maze, const ushort & col, const ushort & row, const char & dir);

    void printInventory() { cout << _inventory << endl;}

    void printHelp() {system("clear"); narate(explainKeys(),0.01);}
};





#endif //CREATURE_H
