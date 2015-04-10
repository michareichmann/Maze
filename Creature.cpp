#include "Creature.h"
#include "Matrix.cpp"

using namespace std;

void Creature::moveTo(cushort & col, cushort & row, const char & dir, Matrix<char> & maze) {

    if (!maze.checkWall(col, row, dir)) {
        if      (dir == 'w') { m_Location.Set(col, row+1); }
        else if (dir == 'a') { m_Location.Set(col-1, row); }
        else if (dir == 's') { m_Location.Set(col, row-1); }
        else if (dir == 'd') { m_Location.Set(col+1, row); }
    }
}

void Creature::lookMap(Matrix<char> & maze, Matrix<char> & emptyMaze){

    system("clear");
    if (!_inventory.count("Match")) narate("You got no matches!\n",2);
    else {
    _inventory.decrease("Match");
    cout << maze << "\nYou lit 1 Match to look at your Map!\t"; secondsLeft(3); system("clear");;
    cout << emptyMaze << "\nYour Match is out! You got " << _inventory.count("Match") << " left\n";
    }
}


void Creature::breakWall(Matrix<char> & maze, const ushort & col, const ushort & row, const char & dir){

    if (!_inventory.count("Sledgehammer")) cout << "You're out of Sledgehammers!\n";
    else if (maze.checkOuterWall(col,row,dir)) cout << "You can't break an outer Wall\n";
    else {
        if (maze.checkWall(col, row, dir) ) {
        maze.deleteLine(col, row, dir);
        _inventory.decrease("Sledgehammer");
        cout << "You crushed the wall with 1 Sledgehammer! You got " << _inventory.count("Sledgehammer") << " left\n";
        }
        else cout << "There is no Wall to break!\n";
    }
}

void Creature::createInventory(){

_inventory.addItem("Sledgehammer",2);
_inventory.addItem("Match",2);
_inventory.addItem("Map\t",1);

}
