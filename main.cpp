#include "Point.h"
#include "Creature.h"
#include "Inventory.h"
#include "Matrix.cpp"
#include "Setup.h"

using namespace std;

int main()
{

    /**setup your creature*/

    narate(welcome,8);
    narate(proceed,0.01); c = getch(); system("clear");
    narate(enterName,2);
    cin >> sName; system("clear");
    Creature creature(sName, Point(1,1), Inventory());
    creature.createInventory();


    /**setup the labyrinth*/

    narate(enterDifficulty(),2) ;
    nDifficulty = tellDifficulty();
    Matrix<char> maze(nDifficulty); maze.randomMaze();
    Matrix<char> emptyMaze(nDifficulty); emptyMaze.clearLines();
//    Matrix<char> mapMaze(nDifficulty);
    Point farthest = maze.farthestPoint(); ushort winx = farthest.x(), winy = farthest.y();
    emptyMaze.set(winx,winy,'x');
    string dir("00");
    narate(intro,3); c = getch();
    narate(goOn,3);
    startGame(); system("clear");
    narate(inventory,3);
    creature.printInventory(); c = getch(); system("clear");

    while (true)
    {
        ushort x = creature.x();
        ushort y = creature.y();
        if (x==winx && y==winy) {cout << "YOU FOUND THE TREASURE!! CONGRATULATIONS!!!\n\n"; break;}

        emptyMaze.set(x,y,dir[1]);
        cout << emptyMaze << endl;
        emptyMaze.reset(x,y);
jump:
        dir[0] = getch();

        /** create the symbol at the pos of your creature*/
        maze.set(x,y,dir[1]);

        /**move to new direction and save the old one*/
        if (dir[0] == 'w' || dir[0] == 'a'|| dir[0] == 's'|| dir[0] == 'd')
                                { creature.moveTo(x,y,dir[0],maze); dir[1]=dir[0];  }

        /**action commands*/
        else if (dir[0] == 'h') { creature.printHelp();                goto jump;   }
        else if (dir[0] == 'p') { creature.position();                 goto jump;   }
        else if (dir[0] == 'm') { creature.lookMap(maze,emptyMaze);    goto jump;   }
        else if (dir[0] == 'b') { creature.breakWall(maze,x,y,dir[1]); goto jump;   }
        else if (dir[0] == 'i') { creature.printInventory();           goto jump;   }

        /**quit programm*/
        else if (dir[0] == '-') {narate(bye,8); exit(2);}

        /**if no condition was satisfied*/
        else     goto jump;

        /** delete the symbol at the pos of your creature*/
        maze.reset(x,y);
        system("clear");

    }



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
