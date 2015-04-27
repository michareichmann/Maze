#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;
typedef pair<uint16_t,uint16_t> nPair;

class Point {

private:
    double m_dX, m_dY, m_dZ;


public:
    Point(): m_dX(0), m_dY(0), m_dZ(0) {};
    Point(double dX, double dY, double dZ): m_dX(dX), m_dY(dY), m_dZ(dZ) {}
    Point(double dX, double dY): m_dX(dX), m_dY(dY) {}


    double x() {return m_dX;}
    double y() {return m_dY;}
    double z() {return m_dZ;}
    void Set(double dX, double dY) {m_dX = dX, m_dY = dY;}
    void Set(double dX, double dY, double dZ) {m_dX = dX, m_dY = dY, m_dZ = dZ;}

    /** overloaded I/O operators to print and insert the Point*/
    friend ostream & operator<<(ostream & out, Point & c1)
    {
        if (c1.z() <0.001 && c1.z() > -0.001)
            out << "(" << c1.x() << ", " <<  c1.y()<< ")";
        else
        out << "(" << c1.x() << ", " <<  c1.y() << ", " << c1.z() << ")";
        return out;
    }

    friend istream & operator>>(istream & in, Point & c1)
    {
        in >> c1.m_dX >> c1.m_dY;
        return in;
    }

};

template <typename T> class Matrix {

private:
    std::vector<std::vector<T> > _mat;
    Point _point;
    unsigned _rows;
    unsigned _cols;

public:
    /**constructors*/
    Matrix() {};
    void construct(uint16_t & nRows, uint16_t & nCols);
    Matrix(uint16_t rows, uint16_t cols, bool bEmpty = false) {construct(rows, cols); if (bEmpty) clearAll();}
    Matrix(uint16_t difficulty);
    //Matrix(uint16_t nSize, bool bConstruct, bool bConstr);

    /**Access functions*/
    T & operator()(const unsigned& row, const unsigned& col);
    unsigned rows() const {return this->_rows;}
    unsigned cols() const {return this->_cols;}

    /**matrix operations*/
    void set(unsigned row, unsigned col, char sign);                        /** sets a specific sign into a single box*/
    void reset(unsigned row, unsigned col);                                 /** clears a sign in a single box*/
    void reset();                                                           /** clears the signs of all boxes*/
    void clearLines();                                                      /** clears all the inner lines*/
    void clearAllLines();                                                   /** clears all lines */
    void clearAll();                                                        /** clears everything*/
    void fillLines();                                                       /** sets all the inner lines*/
    void deleteLine(unsigned row, unsigned col, char dir);                  /** clears the wall of a box in the given direction*/
    void buildLine(uint16_t row, uint16_t col, char dir);                       /** build a wall of a box in the given direction*/
    void printMatrix();                                                     /** prints the full Matrix*/
    void showMaze(uint16_t & col, uint16_t & row, char & dir,
                Matrix<char> & maze);                                       /** sets the sign of the direction prints the maze and deletes the sign*/

    /**game functions*/
    void randomRoom();                                                      /** creates random rooms */
    void randomMaze();                                                      /** creates a random maze */
    void randomSeedPath(vector<vector<uint16_t> > & buf);                    /** creates a random single path*/
    Point farthestPoint();                                                  /** determines the longest path and sets an 'x' at the endpoint*/
    void pov(uint16_t & col, uint16_t & row, Matrix<char> & maze);              /** shows only the visible walls */


    /**miscellaneous*/
    char createRandomDir();
    char createRandomDir(const char & notDir);
    char createRandomDir(const char & notDir1, const char & notDir2);
    char createRandomDir(const char & notDir1, const char & notDir2, const char & notDir3);
    char createRandomPathDir(const uint16_t & row, const uint16_t & col, const uint16_t & maxRow, const uint16_t & maxCol, const char & cLastdir);
    uint16_t getRandom(uint16_t nMin, uint16_t nMax);
    vector<nPair> difficultyNumbers(uint16_t nMinProduct, uint16_t nMaxProduct);

    /**check functions*/
    bool checkWall(uint16_t row, uint16_t col, char dir);
    bool checkOuterWall(uint16_t row, uint16_t col, char dir);
    bool checkNextField(uint16_t row, uint16_t col, const vector<vector<uint16_t> > & buf);


    /**converter*/
    uint16_t cDir(char & dir, bool col);
    char IntChar(uint16_t dir) {char xdir; dir==0 ? xdir = 'w' : (dir == 1 ? xdir = 'd': (dir== 2 ? xdir = 's': xdir='a')); return xdir;}
    uint16_t CharInt(char xdir) {uint16_t dir; xdir=='w' ? dir =0  : (xdir == 'd' ? dir = 1: (xdir== 's' ? dir = 2: dir=3)); return dir;}
    uint16_t posRow(uint16_t row) { return _rows - ((row-1)*2 + 2); }
    uint16_t posCol(uint16_t col) { return (col -1)*4 + 2; }

    /**overloaded out */
    friend ostream & operator<<(ostream & os, Matrix & c1)
    {
        for (unsigned i=0; i<c1.rows(); i++)
        {
            for (unsigned j=0; j<c1.cols(); j++)
                os << c1(i,j);
            os << endl;
        }
        return os;
    }
    friend class Point;
};


#endif //POINT_H
