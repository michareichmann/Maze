#include "Point.h"
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <sstream>
#include <vector>
#include <unistd.h>


using namespace std;



/**constructors*/

template<typename T>
void Matrix<T>::construct(uint16_t & nRows, uint16_t & nCols){

    nCols = 4*nCols + 1;
    nRows = 2*nRows + 1;
    _mat.resize(nRows);
    for (unsigned i(0); i<nRows; i++)
    {
        _mat[i].resize(nCols);
        for (unsigned j(0); j<nCols; j++)
        {
            if (i==0)       !(j % 4) ? _mat[i][j] = ' ' : _mat[i][j] = '_';
            else if (i%2)   !(j % 4) ? _mat[i][j] = '|' : _mat[i][j] = ' ';
            else            !(j % 4) ? _mat[i][j] = '|' : _mat[i][j] = '_';
        }
    }
    _rows = nRows;
    _cols = nCols;
}

template<typename T>
Matrix<T>::Matrix(uint16_t difficulty) {

    srand(time(0));
    uint16_t nRows, nCols, nPairs;
    vector<nPair> num;
    if (difficulty == 0)        num = difficultyNumbers(25,40);
    else if (difficulty == 1)   num = difficultyNumbers(50,70);
    else if (difficulty == 2)   num = difficultyNumbers(90,110);
    else if (difficulty == 3)   num = difficultyNumbers(120,140);

    nPairs = getRandom(0,num.size()-1);
    nRows = num[nPairs].first;
    nCols = num[nPairs].second;

    construct(nRows, nCols);

}

//template<typename T>
//Matrix<T>::Matrix(uint16_t nSize, bool bConstruct, bool bConstr){
//
//    uint16_t nRows = 2*nSize + 1;
//    uint16_t nCols = 4*nSize + 1;
//    _mat.resize(nRows);
//    for (unsigned i(0); i<nRows; i++) {
//        _mat[i].resize(nCols);
//        for (unsigned j(0); j<nCols; j++) {
//            _mat[i][j] = ' ';
//        }
//    }
//    _rows = nRows;
//    _cols = nCols;
//}

/**accessor*/

template<typename T>
T & Matrix<T>::operator()(const unsigned& row, const unsigned& col){
        return this->_mat[row][col];}


/**game functions*/

template<typename T>
void Matrix<T>::randomRoom(){
    srand(time(0));
    uint16_t maxRow = (_rows-1)/2;
    uint16_t maxCol = (_cols-1)/4;
    for (uint16_t row(1); row<=maxRow; row++)
    {
        for (uint16_t col(1); col<=maxCol; col++)
        {
            char dir = createRandomDir();
            if      (row == 1 && col == 1)           {while (true) { dir = createRandomDir(); if (dir == 's' || dir == 'a') continue;else { deleteLine(col, row, dir); break;}}}
            else if (row == 1 && col == maxCol)      {while (true) { dir = createRandomDir(); if (dir == 's' || dir == 'd') continue;else { deleteLine(col, row, dir); break;}}}
            else if (row == maxRow && col == 1)      {while (true) { dir = createRandomDir(); if (dir == 'w' || dir == 'a') continue;else { deleteLine(col, row, dir); break;}}}
            else if (row == maxRow && col == maxCol) {while (true) { dir = createRandomDir(); if (dir == 'w' || dir == 'd') continue;else { deleteLine(col, row, dir); break;}}}
            else if (row == 1)      {while (true) { dir = createRandomDir(); if (dir == 's') continue;else { deleteLine(col, row, dir); break;}}}
            else if (col == 1)      {while (true) { dir = createRandomDir(); if (dir == 'a') continue;else { deleteLine(col, row, dir); break;}}}
            else if (row == maxRow) {while (true) { dir = createRandomDir(); if (dir == 'w') continue;else { deleteLine(col, row, dir); break;}}}
            else if (col == maxCol) {while (true) { dir = createRandomDir(); if (dir == 'd') continue;else { deleteLine(col, row, dir); break;}}}
            else                    deleteLine(row, col, dir);
        }
    }
}

template<typename T>
void Matrix<T>::randomMaze(){

    /**create buffer to save the events*/
    srand(time(0));
    vector<vector<uint16_t> > buf;

    /**instantiate starting pos*/
    buf.resize(1); buf[0].resize(3,1);

    /**create first random path through the maze*/
    randomSeedPath(buf);

    uint16_t start, randPos;
    for (uint16_t nPaths(0); nPaths < 60; nPaths++){

        /**instatiate new random new starting position of old path*/
        start = buf.size();
        randPos = rand() % (start-2) +1;

        buf.resize(start+1); buf[start].resize(3);
        for (uint16_t i(0); i<3;i++)
            buf[start][i] = buf[randPos][i];

        /** for printing the randomly chosen seed*/
//        cout << randPos << " -> " << buf[start][0] << " " << buf[start][1] << " " << buf[start][2] << endl << endl;

        /**create nth random path through the maze*/
        randomSeedPath(buf);
    }

    /** for printing the whole buffer*/
//    for (int i(0); i<buf.size(); i++){
//        cout << buf[i][0] << " " << buf[i][1] << " -> ";
//        if ((i+1)%10==0) cout << endl;
//    }
    //cout << endl;
    //cout << endl;
    //randomPath(buf);
}

template<typename T>
void Matrix<T>::randomSeedPath(vector<vector<uint16_t> > & buf){

    /**instantiate new starting point*/
    uint16_t start = buf.size()-1;

    uint16_t maxRow = (_rows-1)/2, maxCol = (_cols-1)/4;
    uint16_t row, col;

    /**starting point*/
    uint16_t index(start);
    char dir, cLastdir;

    uint16_t maxLength = getRandom(5,50); /**FIXME should depend on the size of the map*/
    for (uint16_t it(0); it<maxLength; it++){
        cLastdir = IntChar((buf[index][2]+2)%4);
        row = buf[index][0]; col = buf[index][1];

        if (it==0)  dir = createRandomPathDir(row, col, maxRow, maxCol, '5');      /** '5' tells the function to discard the lastDir for the first seed*/
        else        dir = createRandomPathDir(row, col, maxRow, maxCol, cLastdir);

        /** break the loop if all surrounding walls are either outer walls or walls to recent fields of the path*/
        uint16_t check(0);
        for (uint16_t allDir(0); allDir<4; allDir++){
            char cAllDir = IntChar(allDir);
            bool outerWall = checkOuterWall(col, row, cAllDir);
            bool nextField = checkNextField(row + cDir(cAllDir,false), col + cDir(cAllDir,true), buf);
            if ( outerWall || nextField) check++;
            else break;
        }
        if (check == 4) break;

        it++;
        if (checkNextField(row + cDir(dir,false), col + cDir(dir,true), buf)) continue;

        deleteLine(col, row, dir);
        buf.resize(index+2); buf[index+1].resize(3);
        buf[index+1][0] = row + cDir(dir, false);
        buf[index+1][1] = col + cDir(dir,true);
        buf[index+1][2] = CharInt(dir);
        index++;



    /**for visualising the creation process*/
//       set(col, row,0);
//       for (unsigned i=0; i<_rows; i++)
//        {
//            for (unsigned j=0; j<_cols; j++)
//                cout << _mat[i][j];
//            cout << endl;
//        }
//        reset(col, row);
//        usleep(100000);

    }
    /**for printing the buffer*/
//    for (int i(start); i<buf.size(); i++){
//        cout << buf[i][0] << " " << buf[i][1] << " -> ";
//        if ((i+1)%10==0) cout << endl;
//    }
    //cout << endl << endl;
}

template<typename T>
Point Matrix<T>::farthestPoint(){

    uint16_t maxRow = (_rows-1)/2, maxCol = (_cols-1)/4;

    uint16_t pathLength, row, col, lastdir(0), lastway, nWays(0), index(1),it(0);
    vector<vector<uint16_t> > buf;
    vector<vector<uint16_t> > endPoints;
    buf.resize(1); buf[0].resize(6,1); buf[0][2]=0; buf[0][3]=5; buf[0][4]=2; /**first one*/

while (it<30) {

    row = buf[it][0]; col = buf[it][1];lastdir = buf[it][3]; lastway = buf[it][4]; pathLength = buf[it][2];
//    cout << "coods " << row << " " << col << " lastway " << lastway <<" lastdir " << lastdir <<endl;

    for (uint16_t i(0); i<(maxRow*maxCol); i++){

        /**save the crossings*/
        nWays = 0;
        if(i==0)    {for (uint16_t j(0); j<4; j++) if (!checkWall(col, row, IntChar(j)) && j!=(lastdir) && j!=lastway) nWays++;}
        else        {for (uint16_t j(0); j<4; j++) if (!checkWall(col, row, IntChar(j)) && j!=(lastdir+2)%4) nWays++;}
//        cout << i << " " << nWays << " -> " << row << " " << col <<" " << lastdir <<endl;
        if (nWays == 3) cout << "rare Exception\n";
        if (nWays>=2) {
            buf.resize(index+1);
            buf[index].push_back(row); buf[index].push_back(col); buf[index].push_back(pathLength); buf[index].push_back((lastdir+2)%4);
            for (uint16_t j(0); j<4; j++) {if (!checkWall(col, row, IntChar(j))&& j!=(lastdir+2)%4) buf[index].push_back(j);}
            index++;
        }
        /**stop the loop to start*/
        if (nWays==0) {
        endPoints.resize(it+1); endPoints[it].push_back(row); endPoints[it].push_back(col); endPoints[it].push_back(pathLength);
        //cout << row << " " << col <<" " << pathLength <<endl;
        break;
        }


        /**if there is a crossing choose w over d over s over a*/
        if (i==0){
            if      (!checkWall(col,row,'d') && lastdir != 1 && lastway !=1)   {pathLength++; col++;lastdir = 1;}
            else if (!checkWall(col,row,'s') && lastdir != 2 && lastway !=2)   {pathLength++; row--;lastdir = 2;}
            else if (!checkWall(col,row,'a') && lastdir != 3 && lastway !=3)   {pathLength++; col--;lastdir = 3;}
        }
        else {
            if      (!checkWall(col,row,'w') && lastdir != 2)   {pathLength++; row++;lastdir = 0;}
            else if (!checkWall(col,row,'d') && lastdir != 3)   {pathLength++; col++;lastdir = 1;}
            else if (!checkWall(col,row,'s') && lastdir != 0)   {pathLength++; row--;lastdir = 2;}
            else if (!checkWall(col,row,'a') && lastdir != 1)   {pathLength++; col--;lastdir = 3;}
        }

    }
    /**printing an 'x' at every endpoint*/
//    col = (col -1)*4 +2; row = _rows - ((row-1)*2 + 2) ;
//    _mat[row][col] = 'x';

    /**break condition*/
    if (buf.size() == it+1) break;
    it++;
}/**end of while loop*/

    /** find the endpoint with the longest path and print an 'x' there*/
    uint16_t x(0);
    for (uint16_t i(1);i<endPoints.size();i++){
        if (endPoints[i][2] > endPoints[x][2]) x=i;
    }
    row = endPoints[x][0]; col = endPoints[x][1];
    Point farthest(col,row);
    col = (col -1)*4 +2; row = _rows - ((row-1)*2 + 2) ;
    //_mat[row][col] = 'x';   //for printing an x at the endpoint

    /** print all the endpoints and length of the path to get there*/
//    for (uint16_t i(0);i<endPoints.size();i++){
//        for (int j(0); j<3;j++)
//            cout << endPoints[i][j] << " ";
//        cout << endl;
//    }

    return farthest;
}

template<typename T>
void Matrix<T>::pov(uint16_t & col, uint16_t & row, Matrix<char> & maze){
    uint16_t mcol = col, mrow = row, it;
    char cDir;
    uint16_t devRow(3), devCol(3); /** position in the center view*/

        for (uint16_t dir2(0); dir2 < 4; dir2++){
        it = 0;
jump:
            for (uint16_t dir1(0); dir1 < 4; dir1++){
                cDir = IntChar(dir1);
                if (maze.checkWall(col, row, cDir)) buildLine(devCol, devRow, cDir);
            }
            cDir = IntChar(dir2);
            if (!maze.checkWall(col, row, cDir) && it<2){
                row     += (-dir2+1)%2;
                col     += (-dir2+2)%2;
                devCol  += (-dir2+2)%2;
                devRow  += (-dir2+1)%2;
                it++;
                goto jump;
            }
            else {
                row = mrow; col = mcol;
                devCol = devRow = 3;
            }
        }
}


/**matrix operations*/

template<typename T>
void Matrix<T>::set(unsigned col, unsigned row, char sign){
    col = (col -1)*4 +2;
    row = _rows - ((row-1)*2 + 2) ;
//    sign == 'w' ? _mat[row][col] = '^' : (sign == 'd' ? _mat[row][col] = '>' : (sign == 'a' ? _mat[row][col] = '<' : (sign == 's' ? _mat[row][col] = 'v': _mat[row][col] = '.')));
    if      (sign == 'w') _mat[row][col] = '^';
    else if (sign == 'd') _mat[row][col] = '>';
    else if (sign == 's') _mat[row][col] = 'v';
    else if (sign == 'a') _mat[row][col] = '<';
    else if (sign == 'x') _mat[row][col] = 'x';
    else                  _mat[row][col] = '.';
}

template<typename T>
void Matrix<T>::reset(unsigned col, unsigned row){
    col = (col -1)*4 +2;
    row = _rows - ((row-1)*2 + 2) ;
    _mat[row][col] = ' ';
}

template<typename T>
void Matrix<T>::reset(){
    for (int row(0); row < (_rows-1)/2; row++)
        for (int col(0); col < (_cols-1)/4; col++)
            _mat[_rows - (row*2 + 2)][col*4 +2] = ' ';
}

template<typename T>
void Matrix<T>::clearLines(){

    for (uint16_t row(0); row < _rows; row++) {
        for (uint16_t col(1); col < _cols -1; col++) {
            if (col % 4 == 0)               _mat[row][col] = ' ';
            if (row == 0 || row == _rows-1) _mat[row][col] = '_';
            else if (row % 2 == 0)          _mat[row][col] = ' ';
        }
    }
}

template<typename T>
void Matrix<T>::clearAllLines(){

     for (uint16_t row(0); row < _rows; row++) {
        for (uint16_t col(0); col < _cols; col++) {
            if (col % 4 == 0) _mat[row][col] = ' ';
            if (row % 2 == 0) _mat[row][col] = ' ';
        }
    }
}

template<typename T>
void Matrix<T>::clearAll(){

    for (uint16_t row(0); row < _rows; row++) {
        for (uint16_t col(0); col < _cols; col++) {
            _mat[row][col] = ' ';
        }
    }
}

template<typename T>
void Matrix<T>::fillLines(){
    for (unsigned row(0); row<_rows; row++)
    {
        for (unsigned col(0); col<_cols; col++)
        {
            if (row==0)       !(col % 4) ? _mat[row][col] = ' ' : _mat[row][col] = '_';
            else if (row%2)   !(col % 4) ? _mat[row][col] = '|' : _mat[row][col] = ' ';
            else              !(col % 4) ? _mat[row][col] = '|' : _mat[row][col] = '_';
        }
    }

}

template<typename T>
void Matrix<T>::deleteLine(unsigned col, unsigned row, char dir){

    col = (col -1)*4 +2; row = _rows - ((row-1)*2 + 2);
    if (dir == 'w')         _mat[row-1][col-1] = _mat[row-1][col] = _mat[row-1][col+1] = ' ';
    else if (dir == 's')    _mat[row+1][col-1] = _mat[row+1][col] = _mat[row+1][col+1] = ' ';
    else if (dir == 'a')    _mat[row][col-2] = _mat[row+1][col-2] = ' ';
    else if (dir == 'd')    _mat[row][col+2] = _mat[row+1][col+2] = ' ';
}

template<typename T>
void Matrix<T>::buildLine(uint16_t col, uint16_t row, char dir){
    col = (col -1)*4 +2;
    row = _rows - ((row-1)*2 + 2);
    if (dir == 'w')         _mat[row-1][col-1] = _mat[row-1][col] = _mat[row-1][col+1] = '_';
    else if (dir == 's')    _mat[row+1][col-1] = _mat[row+1][col] = _mat[row+1][col+1] = '_';
    else if (dir == 'a')    _mat[row][col-2] = _mat[row+1][col-2] = '|';
    else if (dir == 'd')    _mat[row][col+2] = _mat[row+1][col+2] = '|';
}

template<typename T>
void Matrix<T>::printMatrix(){
    for (uint16_t i(0); i<_rows; i++)
        {
            cout << "\t\t\t";
            for (uint16_t j(0); j<_cols; j++)
                cout << _mat[i][j];
            cout << "\n";
        }
}

template<typename T>
void Matrix<T>::showMaze(uint16_t & col, uint16_t & row, char & dir, Matrix<char> & maze){

    pov(col,row,maze);
    set(3, 3, dir);
    cout << "\v\v\v\v";
    printMatrix();
    reset(3, 3);
    clearAllLines();
}

/**miscellaneous*/

template<typename T>
char Matrix<T>::createRandomDir(){
    unsigned short x = rand() % 4;
    char dir;
    x==0 ? dir='w' : (x==1 ? dir='d' :(x==2 ? dir='s' : dir='a'));
    return dir;
}

template<typename T>
char Matrix<T>::createRandomDir(const char & notDir){
    uint16_t x = rand() % 3;
    uint16_t sNotDir = CharInt(notDir);
    uint16_t dir;
    if (notDir=='5') dir=CharInt(createRandomDir());
    else {
        x==0 ? dir = (sNotDir+1)%4 : (x==1 ? dir = (sNotDir+2)%4 : dir = (sNotDir+3)%4);
    }
    char cDir = IntChar(dir);
    return cDir;
}

template<typename T>
char Matrix<T>::createRandomDir(const char & notDir1, const char & notDir2){
    uint16_t x = rand() % 2;
    uint16_t sNotDir1 = CharInt(notDir1), sNotDir2  = CharInt(notDir2);
    uint16_t dir;
    uint16_t largerDir = ((sNotDir1+1)%4==sNotDir2 ? sNotDir2 : sNotDir1);
    if (notDir2=='5')                        {dir = CharInt(createRandomDir(notDir1));}
    else {
        if      (sNotDir1 == (sNotDir2+2)%4) {x==0 ? dir=(sNotDir1+1)%4 : dir=(sNotDir1+3)%4;}
        else if (sNotDir1 == sNotDir2)       {cout << "This is not supposed to happen!\n";}
        else                                 {x==0 ? dir=(largerDir+1)%4 : dir=(largerDir+2)%4;}
    }
    char xdir = IntChar(dir);
    return xdir;

}

template<typename T>
char Matrix<T>::createRandomDir(const char & notDir1, const char & notDir2, const char & notDir3){
    uint16_t s1 = CharInt(notDir1), s2 = CharInt(notDir2), s3  = CharInt(notDir3);
    uint16_t dir;
    if (notDir3=='5')   {dir = CharInt(createRandomDir(notDir1,notDir2));}
    else                dir = 6-s1-s2-s3;
    char cdir = IntChar(dir);
    return cdir;
}

template<typename T>
char Matrix<T>::createRandomPathDir(const uint16_t & row, const uint16_t & col, const uint16_t & maxRow, const uint16_t & maxCol, const char & cLastdir) {

    char dir;

    if (row == 1 && col == 1)                   dir = createRandomDir('s','a',cLastdir);
    else if (row == 1 && col == maxCol)         dir = createRandomDir('s','d',cLastdir);
    else if (row == maxRow && col == 1)         dir = createRandomDir('w','a',cLastdir);
    else if (row == maxRow && col == maxCol)    dir = createRandomDir('w','d',cLastdir);//{cout << "\n"; break;}
    else if (row == 1)                          dir = createRandomDir('s',cLastdir);
    else if (col == 1)                          dir = createRandomDir('a',cLastdir);
    else if (row == maxRow)                     dir = createRandomDir('w',cLastdir);
    else if (col == maxCol)                     dir = createRandomDir('d',cLastdir);
    else                                        dir = createRandomDir(cLastdir);

    return dir;
    }

template<typename T>
uint16_t Matrix<T>::getRandom(uint16_t nMin, uint16_t nMax){
    uint16_t random = rand() % (nMax-nMin+1);
    random += nMin;
    return random;
}

template<typename T>
vector<nPair> Matrix<T>::difficultyNumbers(uint16_t nMinProduct, uint16_t nMaxProduct){
    vector<nPair> num;
    uint16_t it(1);
            for (uint16_t i(4); i<17; i++){
                for (uint16_t j(5); j<17; j++){
                    if (i*j>=nMinProduct && i*j <nMaxProduct) {
                    num.resize(it);
                    num[it-1].first = i; num[it-1].second = j;
                    it++;
                    }
                }
            }
    return num;
}


/**checker functions */

template<typename T>
bool Matrix<T>::checkWall(uint16_t col,uint16_t row, char dir){
    bool checkWall(false);
    col = (col -1)*4 +2;
    row = _rows - ((row-1)*2 + 2);
    if      (dir == 's' && _mat[row+1][col] == '_') checkWall = true;
    else if (dir == 'w' && _mat[row-1][col] == '_') checkWall = true;
    else if (dir == 'd' && _mat[row][col+2] == '|') checkWall = true;
    else if (dir == 'a' && _mat[row][col-2] == '|') checkWall = true;
    return checkWall;
}

template<typename T>
bool Matrix<T>::checkOuterWall(uint16_t col,uint16_t row, char dir){


    uint16_t maxRow = (_rows-1)/2;
    uint16_t maxCol = (_cols-1)/4;
    bool checkOuterWall(false);
    if ((row==1 && dir=='s') || (row==maxRow && dir=='w') || (col==1 && dir=='a') || (col==maxCol && dir=='d'))
        {
            checkOuterWall = true;
        }
    return checkOuterWall;
}

template<typename T>
bool Matrix<T>::checkNextField(uint16_t row, uint16_t col, const vector<vector<uint16_t> > & buf){

    bool check(false);
    for (uint16_t i(0); i < buf.size(); i++ )
    {
        //cout <<"row: " << buf[i][0] << " col: " << buf[i][1] << endl;
        if (buf[i][0] == row && buf[i][1] == col) check = true;
    }
        return check;
}



/**converters*/

template<typename T>
uint16_t Matrix<T>::cDir(char & dir, bool col){

    uint16_t num, nDir = CharInt(dir);
    if (!col)    num = (-nDir+1)%2;
    else        num = (-nDir+2)%2;

    return num;
}










