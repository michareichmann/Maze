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


public:
    Creature() { }
    Creature(string sName, const Point & cLocation, const Inventory & cInventory): m_sName(sName), m_Location(cLocation), _inventory(cInventory) { }

    /** getter function for the positon*/
    uint16_t x() {return m_Location.x();}
    uint16_t y() {return m_Location.y();}
    uint16_t count(string sItemName) {for (uint16_t i(0); i<_inventory.size(); i++){ if (_inventory.name(i)==sItemName) {return _inventory.count(i); break;}}}

    friend ostream & operator<<(ostream & os, Creature & c1)
    {
        os << c1.m_sName << " is at " << c1.m_Location;
        return os;
    }

    /** setter functions*/

    void createInventory();

    /** actions of the creature*/
    void moveTo(const uint16_t & col, const uint16_t & row, const char & dir, Matrix<char> & maze);

    void position() {cout << m_sName << " is at " << m_Location << endl;}

    void lookMap(Matrix<char> & maze, Matrix<char> & emptyMaze, uint16_t & col, uint16_t & row, char & dir);

    void breakWall(Matrix<char> & emptymaze, Matrix<char> & maze, uint16_t & col, uint16_t & row, char & dir);

    void printInventory() { cout << _inventory << endl;}

    void printHelp() {clearScreen(); narate(explainKeys(),0.01);}

    void locateTreasure(Point & farthest, uint16_t & col, uint16_t & row);
};





#endif //CREATURE_H
