#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>

using namespace std;
typedef unsigned short ushort;
typedef const unsigned short cushort;
typedef pair<ushort,ushort> nPair;

class Point
{
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
    void construct(ushort nRows, ushort nCols);
    Matrix(unsigned rows, unsigned cols) {construct(rows, cols);}
    Matrix(ushort difficulty);
    Matrix(const Matrix<T>& rhs);
    //virtual ~Matrix();

    /**Access functions*/
    T & operator()(const unsigned& row, const unsigned& col);
    unsigned rows() const {return this->_rows;}
    unsigned cols() const {return this->_cols;}

    /**setter functions*/
    void set(unsigned row, unsigned col, char sign);
    void clearLines();
    void fillLines();
    void deleteLine(unsigned row, unsigned col, char dir);
    void randomRoom();
    void randomMaze();
    void randomSeedPath(vector<vector<ushort> > & buf);
    Point farthestPoint();

    /**reset to default*/
    void reset(unsigned row, unsigned col);
    void reset();

    /**miscellaneous*/
    char createRandomDir();
    char createRandomDir(const char & notDir);
    char createRandomDir(const char & notDir1, const char & notDir2);
    char createRandomDir(const char & notDir1, const char & notDir2, const char & notDir3);
    char createRandomPathDir(const ushort & row, const ushort & col, const ushort & maxRow, const ushort & maxCol, const char & cLastdir);
    bool checkWall(ushort row, ushort col, char dir);
    bool checkOuterWall(ushort row, ushort col, char dir);
    bool checkNextField(ushort row, ushort col, const vector<vector<ushort> > & buf);
    ushort getRandom(ushort nMin, ushort nMax);
    vector<nPair> difficultyNumbers(ushort nMinProduct, ushort nMaxProduct);


    /**converter*/
    ushort cDir(char dir, bool cood);
    char IntChar(ushort dir) {char xdir; dir==0 ? xdir = 'w' : (dir == 1 ? xdir = 'd': (dir== 2 ? xdir = 's': xdir='a')); return xdir;}
    ushort CharInt(char xdir) {ushort dir; xdir=='w' ? dir =0  : (xdir == 'd' ? dir = 1: (xdir== 's' ? dir = 2: dir=3)); return dir;}

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
