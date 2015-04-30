
#include "Setup.h"
#include "Creature.h"
#include "Inventory.h"
#include "Matrix.cpp"

using namespace std;

/**TODO*/

/** fix rare exception
    improve pov to see all the neccessary walls
    implement enemies
    implement dig for treasure
    durability of items
    larger empty map
    fix/improve random Room
    implement size dependend length of the random paths
    adjust difficulty to larger maps
*/


int main()
{
    /**DEBUGMODE*/

//    Creature creature("Micha", Point(1,1), Inventory()); creature.createInventory();
//    Matrix<char> maze(10,10); maze.randomMaze();
//    Matrix<char> emptyMaze(5,5,true);
//    Point farthest = maze.farthestPoint(); uint16_t winx = farthest.x(), winy = farthest.y();
//    string dir("00");

    /**GAMEMODE*/

    /**setup your creature*/

    clearScreen();
    printLines("maze.txt");
    narate(proceed,0.1); c = _getch(); clearScreen();
    narate(enterName,4);
    cin >> sName; clearScreen();
    Creature creature(sName, Point(1,1), Inventory());
    creature.createInventory();


    /**setup the labyrinth*/

    narate(enterDifficulty(),5) ;
    Matrix<char> maze(tellDifficulty()); maze.randomMaze();
    Matrix<char> emptyMaze(5,5,true);
    Point farthest = maze.farthestPoint();
    uint16_t winx = farthest.x(), winy = farthest.y();
    string dir("00");
    narate(intro,4); c = _getch();
    narate(goOn,4);
    startGame(); clearScreen();
    narate(inventory,4);
    creature.printInventory(); c = _getch(); clearScreen();
    narate(help,4);c = _getch(); clearScreen();

    /**GAMECODE*/


    bool jump(false);

    while (true)
    {
        uint16_t x = creature.x();
        uint16_t y = creature.y();

        /**visualization of the maze*/
        if (!jump) {
            clearScreen();
            emptyMaze.showMaze(x,y,dir[1],maze);
        }
        jump = false;

        /**goal*/
        if (x==winx && y==winy) {cout << "YOU FOUND THE TREASURE!! CONGRATULATIONS!!!\n\n"; printLines("sign.txt"); c = _getch(); break;}

        dir[0] = _getch();

        /** create the symbol at the pos of your creature*/
        maze.set(x,y,dir[1]);

        /**move to new direction and save the old one*/
        if (dir[0] == 'w' || dir[0] == 'a'|| dir[0] == 's'|| dir[0] == 'd')
                                { creature.moveTo(x,y,dir[0],maze); dir[1]=dir[0];  }

        /**action commands*/
        else if (dir[0] == 'h') { creature.printHelp();                                     jump = true;   }
        else if (dir[0] == 'p') { creature.position();                                      jump = true;   }
        else if (dir[0] == 'm') { creature.lookMap(maze, emptyMaze, x,y, dir[1]);           jump = true;   }
        else if (dir[0] == 'b') { creature.breakWall(emptyMaze, maze,x,y,dir[1]);           jump = true;   }
        else if (dir[0] == 'i') { creature.printInventory();                                jump = true;   }
        else if (dir[0] == 't') { creature.locateTreasure(farthest, x, y);                  jump = true;   }

        /**quit program*/
        else if (dir[0] == '-') {narate(bye,8); exit(2);}

        /**if no condition was satisfied*/
        else     jump = true;


        /** delete the symbol at the pos of your creature*/
        maze.reset(x,y);

    }



    return 0;
}
