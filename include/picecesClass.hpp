#ifndef PIECES_CLASS_HPP
#define PIECES_CLASS_HPP
#include <vector>
#include <varhelp.h>
class pawn {//pawn's code on the grid is 1 for white 2 for black

    private:

    bool hasmoved = false, sideprivate;
    void givelegalmove(short movegrid[8][8]);
    std::vector<short> legalcells;
    short oldcell;

    public:
    short posx, posy, cellpublic;
    bool giveside(){return sideprivate;}
    const std::vector<short>& getLegalCells() const { return legalcells; }
    pawn(bool side,column number,short grid[8][8]);//side 1 if white 0 if black
    bool istaken(short grid[8][8]);
    void checkMovement(short cell , short grid[8][8], short movegrid[8][8]);
    void move(short cell, short grid[8][8]);
};

#endif