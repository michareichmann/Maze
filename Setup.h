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
#endif //WINDOWS

#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include "Point.h"
#include <cmath>
#include <fstream>


/**text defitions*/
static string enterName = "Enter the name of your creature: ";
static string intro     = "You reached a pitch black maze and want to find the hidden treasure! Go on and try your luck!\n\n";
static string inventory = "You begin with:\n\n";
static string goOn      = "You want start MAZE (y/n) ? ";
static string help      = "You can press 'h' at any time to show the assignment of keys.";
static string welcome   = "Greetings! Welcome to MAZE!\n\n";
static string proceed   = "Press any button to proceed.";
static string bye       = "Good Bye and thank you for playing!";
static string quest;        /**query to start the game*/
static string sName;        /**Name of the creature*/
static char c;              /**placeholder*/
static char cDifficulty;    /**responsible for the size of the maze*/

/** texts in stringstreams */
string enterDifficulty();
string explainKeys();

/** setup functions */
void clearScreen();                                 /** clears the last screen in the terminal*/
void sleeep(uint32_t time);                         /** waits for a certain amount of time (time = 1e6 --> 1 sec) */
char _getch();                                      /** function to skip pressing enter after the input*/
void printLines(const char * name);                 /** reads in textfiles and prints line after line with a delay*/
void narate(const string & story, uint32_t speed);  /** function to narate the text*/
void secondsLeft(uint16_t seconds);                 /** waits for the given amount of seconds and prints dots in the meantime*/
uint16_t tellDifficulty();                          /** sets the difficulty based on user input and gives comment accordingly*/
void startGame();                                   /** query wheather to start the game */


#endif // SETUP_H

