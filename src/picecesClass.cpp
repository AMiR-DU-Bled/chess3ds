#include <picecesClass.hpp>
#include <helper.h>
#include <vector>
#include <algorithm>
#include <varhelp.h>
#include <citro2d.h>


    pawn::pawn(bool side,column number){
        short x, y;
        if (side) x = 6;
        else x = 1;
        y = static_cast<short>(number) - 1;
        cellpublic = xytocell(x, y);
        cellToPos(posx,posy,cellpublic);
    }

void pawn::checkMovement(short cell, short grid[8][8], short movegrid[8][8]){
    short x, y, tempx, tempy;
    interpretinput(x, y, cell);
    auto test = std::find(legalcells.begin(), legalcells.end(),cell);
    if (!legalcells.empty()){
        if (test != legalcells.end()){
            interpretinput(tempx, tempy, oldcell);
            grid[tempx][tempy] = 0;
            if (turn) grid[x][y] = 1;
            if (!turn) grid[x][y] = 2;
            if (tempx == x - 2 || tempx == x + 2 )hasmoved = !hasmoved;
            x = -1;
            y = -1; 
            cellpublic = cell;
            cellToPos(posx,posy,cellpublic);
        }
    }
    if (grid[x][y] == 1 && turn){
        oldcell = xytocell(x,y);
        if (!hasmoved){
            if (grid [x-1][y] == 0)legalcells.push_back(xytocell(x-1,y));
            if (grid [x-1][y] == 0 && grid [x-2][y] == 0)legalcells.push_back(xytocell(x-2,y));   
        }
        else if (grid [x-1][y] == 0)legalcells.push_back(xytocell(x-1,y));
    }
    else if (grid[x][y] == 2 && !turn){
        oldcell = xytocell(x,y);
        if (!hasmoved){
            if (grid [x+1][y] == 0)legalcells.push_back(xytocell(x+1,y));
            if (grid [x+1][y] == 0 && grid [x-2][y] == 0)legalcells.push_back(xytocell(x+2,y));
        }
        else if (grid [x+1][y] == 0)legalcells.push_back(xytocell(x+1,y));
    }
    else legalcells.clear();
}