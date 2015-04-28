#ifndef SETUP_H
#define SETUP_H

/** Check for Windows */
#ifdef WINDOWS
#include "windows.h"
#include <conio.h>
#define M_PI 3.141592
#else
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#endif

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include "Point.h"
#include <cmath>

/** function to clear the scree */
#ifdef WINDOWS
inline void clearScreen(){system("cls");}
#else
inline void clearScreen(){ system("clear");}
#endif // WINDOWS

/** function to narate the text*/
inline void narate(const string &story, unsigned int speed){
    speed *=10000;
    uint16_t time = 1;
    for (uint16_t i(0); i<story.size();i++ ){
#ifdef WINDOWS
        if ((story[i-1] == '.' ||story[i-1] == '!' ||story[i-1] == '?')&& i>1 && i<story.size()-2 ) Sleep(1000*time);
        cout << story[i];
        cout.flush();
        Sleep(speed/1000);
#else
        if ((story[i-1] == '.' ||story[i-1] == '!' ||story[i-1] == '?')&& i>1 && i<story.size()-2 ) sleep(time);
        cout << story[i];
        cout.flush();
        usleep(speed);
#endif // WINDOWS
    }

}

inline void secondsLeft(uint16_t seconds){
    unsigned int time = 1000000/4;
    for (uint16_t i=seconds; i<100; i--){
        cout << i << " "; cout.flush();
        if (i==0) break;
        for (uint16_t i(0); i<3;i++){
#ifdef WINDOWS
            Sleep(time/1000);
            cout << "."; cout.flush();
        }
        cout << " "; cout.flush();
        Sleep(time/1000);
#else
            usleep(time);
            cout << "."; cout.flush();
        }
        cout << " "; cout.flush();
        usleep(time);
#endif // WINDOWS
    }
}

static string quest;                   /**query to start the game*/

inline void startGame(){

    while (true){
            cin >> quest;
            if (quest == "y" || quest == "yes") break;
            else if(quest == "n" || quest == "no") {narate("Good Bye!",8); break;}
            else narate("Please enter 'y' or 'n': ",6);
        }
    cout << "\n";

}

/** function to skip pressing enter after the input*/

#ifndef WINDOWS
inline char _getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
#endif

/**Setup texts*/

static char c;                  /**placeholder*/

static string sName;            /**Name of the creature*/

static char cDifficulty;        /**responsible for the size of the maze*/

static string welcome = "Greetings! Welcome to MAZE!\n\n";

static string proceed = "Press any button to proceed.";

inline string explainKeys(){
    stringstream explainKeys;
    explainKeys << "w:\t move up\t\t";
    explainKeys << "a:\t move left\n";
    explainKeys << "s:\t move down\t\t";
    explainKeys << "d:\t move right\n";
    explainKeys << "p:\t position\t\t";
    explainKeys << "i:\t inventory\n";
    explainKeys << "m:\t map\t\t\t";
    explainKeys << "b:\t crush a wall\n";
    explainKeys << "h:\t menu\t\t\t";
    explainKeys << "t:\t locate treasure\n";
    explainKeys << "-:\t end game\n\n";
    return explainKeys.str();
}

static string enterName = "Enter the name of your creature: ";

inline string enterDifficulty(){
    stringstream diff;
    diff << "Enter the difficulty:\n\n";
    diff << "'0' for absolute beginners\n";
    diff << "'1' for easy\n";
    diff << "'2' for medium\n";
    diff << "'3' for hard\n\n";
    diff << "What would you like to choose? ";
    return diff.str();
}

inline uint16_t tellDifficulty(){
     while (true){
        cDifficulty = _getch();
        if      (cDifficulty == '0') {narate("\nYou are such a scaredy cat! You chose very easy!",5); break;}
        else if (cDifficulty == '1' ){narate("\nThat should not be too hard for you. You chose easy!",2); break;}
        else if (cDifficulty == '2') {narate("\nWell this might be a challenge for you. You chose medium!",2); break;}
        else if (cDifficulty == '3') {narate("\nAre you really sure that is not too hard for you? You chose hard!",2); break;}
        else {cout << "\033[2K\033[A\033[2K"; narate("\nYou did not enter a valid difficulty! please try again: ",2);}
    }
    c = _getch(), clearScreen();
    return int(cDifficulty-'0');
}

static string intro = "You reached a pitch black maze and want to find the hidden treasure! Go on and try your luck!\n\n";

static string inventory = "You begin with:\n\n";

static string goOn = "You want start MAZE (y/n) ? ";

static string help = "You can press 'h' at any time to show the assignment of keys.";

static string bye = "Good Bye and thank you for playing!";

#endif // SETUP_H

