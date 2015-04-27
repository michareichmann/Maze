#include "Point.h"
#include "Creature.h"
#include "Inventory.h"
#include "Matrix.cpp"
#include "Setup.h"

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
    crossplatform compile
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

    system("clear");
    narate(welcome,8);
    narate(proceed,0.01); c = getcha(); system("clear");
    narate(enterName,2);
    cin >> sName; system("clear");
    Creature creature(sName, Point(1,1), Inventory());
    creature.createInventory();


    /**setup the labyrinth*/

    narate(enterDifficulty(),2) ;
    Matrix<char> maze(tellDifficulty()); maze.randomMaze();
    Matrix<char> emptyMaze(5,5,true);
    Point farthest = maze.farthestPoint();
    uint16_t winx = farthest.x(), winy = farthest.y();
    string dir("00");
    narate(intro,3); c = getcha();
    narate(goOn,3);
    startGame(); system("clear");
    narate(inventory,3);
    creature.printInventory(); c = getcha(); system("clear");
    narate(help,3);c = getcha(); system("clear");

    /**GAMECODE*/


    bool jump(false);

    while (true)
    {
        uint16_t x = creature.x();
        uint16_t y = creature.y();

        /**visualization of the maze*/
        if (!jump) {
            system("clear");
            emptyMaze.showMaze(x,y,dir[1],maze);
        }
        jump = false;

        /**goal*/
        if (x==winx && y==winy) {cout << "YOU FOUND THE TREASURE!! CONGRATULATIONS!!!\n\n"; break;}

        dir[0] = getcha();

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

//Matrix<char> maze(9,9);
//maze.randomMaze();
//maze.set(5,5,'x');
//maze.printMatrix();
//maze.clearLines();
//maze.printMatrix();
//Matrix<char> blub(9,9);
//blub.clearLines();
//uint16_t col = 8, row = 8;
//blub.pov(col, row, maze);
//
//cout << maze << endl;
//cout << blub << endl;
//while (1){
//    char dir;
//    cin >> col >> row >> dir;
//    cout << maze.checkWall(col, row, dir) << endl;
//}



//Inventory Test(Items("Sledge",5));
//Test.addItem("Candle", 3);
//Test.addItem("boots", 1);
//cout << Test<< endl;
//Inventory Test1;
//cout << Test1;
//Test1.addItem("bla", 5);
//cout << Test1 << endl;







//num.resize(1);
//num[0].first = 2;
//num[0].second = 3;
//cout << num[0].first;


//for (int i(0); i<num.size(); i++)
//    cout << num[i].first << " * " << num[i].second << " = " <<  num[i].first*num[i].second << endl;


//    while (true)
//    {
//        maze.set(1,1,0);
//        maze.fillLines();
//        maze.randomMaze();
//        maze.farthestPoint();
//        cout << maze << endl;
//        int row;
//        cin >> row;
//
//       if (row=='0') break;
//    }

// while (true)
//    {
//        int dir1, dir2;
//        cin >> dir1 >> dir2;
//        for (int i(0); i<4; i++){
//            cout << maze.createRandomPathDir(dir1,dir2,9,9,'5')<< "\n";
//        }
//        cout << endl;
//
//       if (dir1=='0') break;
//    }




    return 0;
}
