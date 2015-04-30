#include "Setup.h"

/**WINDOWS*/
#ifdef WINDOWS
void clearScreen(){system("cls");}
inline void Sleep(uint32_t time){Sleep(time/1000);}
#else
void clearScreen(){ system("clear");}
inline void sleeep(uint32_t time){ usleep(time);}
char _getch() {
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
#endif // WINDOWS

/**STRINGSTREAMS*/

string enterDifficulty(){
    stringstream diff;
    diff << "Enter the difficulty:\n\n";
    diff << "'0' for absolute beginners\n";
    diff << "'1' for easy\n";
    diff << "'2' for medium\n";
    diff << "'3' for hard\n\n";
    diff << "What would you like to choose? ";
    return diff.str();
}

string explainKeys(){
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

/**FUNCTIONS*/

void narate(const string &story, uint32_t speed){
    if      (speed == 1) speed *= 4e4;
    else if (speed == 2) speed *= 2e4;
    else if (speed == 3) speed *= 1e4;
    else if (speed == 4) speed *= 5e3;
    else if (speed == 5) speed *= 25e2;
    uint32_t time = 5e5;
    for (uint16_t i(0); i<story.size();i++ ){
        if ((story[i-1] == '.' ||story[i-1] == '!' ||story[i-1] == '?')&& i>1 && i<story.size()-2 ) sleeep(time);
        cout << story[i];
        cout.flush();
        sleeep(speed);
    }
}

void printLines(const char * name){
    uint32_t wait = 5e4;
    string line;
//    string filename = string("/home/micha/Dropbox/Master Thesis/cpp Tutorial/Maze/")+name;
//    ifstream stream(filename.c_str());
    ifstream stream(name);

    if (stream.is_open())
    {
        while ( getline (stream,line) )
        {
          cout << line << '\n';
          sleeep(wait);
        }
        stream.close();
    }
    else cout << "ERROR: couldn't open file!\n";
}

void secondsLeft(uint16_t seconds){
    uint32_t time = 1e6/4;
    for (uint16_t i=seconds; i<100; i--){
        cout << i << " "; cout.flush();
        if (i==0) break;
        for (uint16_t i(0); i<3;i++){
            sleeep(time);
            cout << "."; cout.flush();
        }
        cout << " "; cout.flush();
        sleeep(time);
    }
}

uint16_t tellDifficulty(){
     while (true){
        cDifficulty = _getch();
        if      (cDifficulty == '0') {narate("\nYou are such a scaredy cat! You chose very easy!",5); break;}
        else if (cDifficulty == '1' ){narate("\nThat should not be too hard for you. You chose easy!",4); break;}
        else if (cDifficulty == '2') {narate("\nWell this might be a challenge for you. You chose medium!",4); break;}
        else if (cDifficulty == '3') {narate("\nAre you really sure that is not too hard for you? You chose hard!",4); break;}
        else {cout << "\033[2K\033[A\033[2K"; narate("\nYou did not enter a valid difficulty! please try again: ",4);}
    }
    c = _getch(), clearScreen();
    return int(cDifficulty-'0');
}

void startGame(){

    while (true){
            cin >> quest;
            if (quest == "y" || quest == "yes") break;
            else if(quest == "n" || quest == "no") {narate("Good Bye!\n\n",2); printLines("sign.txt"); c=_getch(); exit(3);}
            else narate("Please enter 'y' or 'n': ",4);
        }
    cout << "\n";
}