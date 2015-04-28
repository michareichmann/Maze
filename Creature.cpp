#include "Creature.h"
#include "Matrix.cpp"
#include "Setup.h"

using namespace std;

void Creature::moveTo(const uint16_t & col, const uint16_t & row, const char & dir, Matrix<char> & maze) {

    if (!maze.checkWall(col, row, dir)) {
        if      (dir == 'w') { m_Location.Set(col, row+1); }
        else if (dir == 'a') { m_Location.Set(col-1, row); }
        else if (dir == 's') { m_Location.Set(col, row-1); }
        else if (dir == 'd') { m_Location.Set(col+1, row); }
    }
}

void Creature::lookMap(Matrix<char> & maze, Matrix<char> & emptyMaze, uint16_t & col, uint16_t & row, char & dir){

    clearScreen();
    if (!_inventory.count("Match")) narate("You got no matches!\n",2);
    else {
    _inventory.decrease("Match");
    cout << maze << "\nYou lit 1 Match to look at your Map!\t"; secondsLeft(3); clearScreen();
    emptyMaze.showMaze(col, row, dir, maze);
    cout << "\nYour Match is out! You got " << _inventory.count("Match") << " left\n";
    }
}


void Creature::breakWall(Matrix<char> & emptyMaze, Matrix<char> & maze, uint16_t & col, uint16_t & row, char & dir){

    if (!_inventory.count("Sledgehammer")) cout << "You're out of Sledgehammers!\n";
    else if (maze.checkOuterWall(col,row,dir)) cout << "You can't break an outer Wall\n";
    else {
        if (maze.checkWall(col, row, dir) ) {
        maze.deleteLine(col, row, dir);
        emptyMaze.deleteLine(3,3,dir);
        _inventory.decrease("Sledgehammer");
        clearScreen(); emptyMaze.showMaze(col, row, dir, maze);
        cout << "You crushed the wall with 1 Sledgehammer! You got " << _inventory.count("Sledgehammer") << " left\n";
        }
        else cout << "There is no Wall to break!\n";
    }
}

void Creature::createInventory(){

_inventory.addItem("Sledgehammer",2);
_inventory.addItem("Match",2);
_inventory.addItem("Map",1);
_inventory.addItem("Mole",5);
_inventory.addItem("Shovel",3);

}

void Creature::locateTreasure(Point & farthest, uint16_t & col, uint16_t & row){

    /**check inventory*/
    if (!_inventory.count("Mole")) narate("You're out of Sledgehammers!\n",2);

    /** tell the distance to the treasure*/
    double x = farthest.x(), y = farthest.y();
    double distX = x-col, distY = y-row;
    double distance = sqrt(pow(distX,2)+pow(distY,2));
    if      (distance>=10)   narate("You're very far away. ",2);
    else if (distance>=7)    narate("You're still far away. ",2);
    else if (distance>=4)    narate("You're getting closer. ",2);
    else if (distance>=2)    narate("You're close now. ",2);
    else                     narate("The treasure is in your immediate vicinity! ",2);
#ifdef WINDOWS
    Sleep(1000);
#else
    sleep(1);
#endif

    /** tell the direction to the treasure*/
    double angle = 180/M_PI*atan(abs(distY/distX));
    if      (distX < 0 && distY >=0)    angle = 180 - angle;
    else if (distX < 0 && distY < 0)    angle = 180 + angle;
    else if (distX >=0 && distY < 0)    angle = 360 - angle;

    string direction[7] = {"northeastward", "northward", "northwestward", "westward", "southwestward", "southward", "southeastward"};
    if (angle < 22.5 || angle >337.5)   narate("The treasure ist east of you!\n",2);
    for (uint16_t i(0); i < 7; i++)
#ifdef WINDOWS
        if (angle > 22.5+45*i && angle < 67.5+i*45)  {narate("The treasure is ",2); narate(direction[i],2); cout << "!\n";Sleep(1000);}
#else
        if (angle > 22.5+45*i && angle < 67.5+i*45)  {narate("The treasure is ",2); narate(direction[i],2); cout << "!\n";sleep(1);}
#endif

    /** decrease item */

    _inventory.decrease("Mole"); narate("You just used 1 Mole. You got ",2); cout << _inventory.count("Mole"); narate(" left\n",2);

}
