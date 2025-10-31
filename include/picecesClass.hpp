#ifndef PIECES_CLASS_HPP
#define PIECES_CLASS_HPP
#include <vector>
#include <varhelp.h>
class pawn {//pawn's code on the grid is 1 for white 2 for black

    private:

    bool hasmoved = false;
    void givelegalmove(short movegrid[8][8]);
    std::vector<short> legalcells;
    short oldcell;

    public:
    short posx, posy, cellpublic;
    pawn(bool side,column number);//side 1 if white 0 if black
    void checkCell();
    void checkMovement(short cell , short grid[8][8], short movegrid[8][8]);

};

#endif