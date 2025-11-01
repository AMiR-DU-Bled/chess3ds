#include <picecesClass.hpp>
#include <helper.h>
#include <vector>
#include <algorithm>
#include <varhelp.h>
#include <citro2d.h>


pawn::pawn(bool side,column number,short grid[8][8]){
    short x, y;
    if (side) x = 6;
    else x = 1;
    y = static_cast<short>(number) - 1;
    cellpublic = xytocell(x, y);
    if (side) grid[x][y] = 1;
    else grid[x][y] = 2;
    cellToPos(posx,posy,cellpublic);
    sideprivate = side;
}

bool pawn::istaken(short grid[8][8]){
    short x, y;
    celltoxy(x,y,cellpublic);
    if (grid [x][y] != 1 && sideprivate){cellpublic = -1;  return true; }
    if (grid [x][y] != 2 && !sideprivate){cellpublic = -1; return true; }
    else return false;
}

void pawn::checkMovement(short cell, short grid[8][8], short movegrid[8][8]){
    legalcells.clear();
    if (cellpublic != -1){
        short x, y, tempx, tempy;
        celltoxy(x, y, cell);
        if (grid[x][y] == 1){
            oldcell = xytocell(x,y);
            if (!hasmoved){
                if (grid [x-1][y] == 0)legalcells.push_back(xytocell(x-1,y));
                if (grid [x-1][y] == 0 && grid [x-2][y] == 0)legalcells.push_back(xytocell(x-2,y));
                if (grid [x-1][y-1] == 2 || grid [x-1][y-1] == 4 || grid [x-1][y-1] == 6 || grid [x-1][y-1] == 8 || grid [x-1][y-1] == 10)
                legalcells.push_back(xytocell(x-1,y-1));
                if (grid [x-1][y+1] == 2 || grid [x-1][y+1] == 4 || grid [x-1][y+1] == 6 || grid [x-1][y+1] == 8 || grid [x-1][y+1] == 10)
                legalcells.push_back(xytocell(x-1,y+1));
            }
            else{
                if (grid [x-1][y] == 0)legalcells.push_back(xytocell(x-1,y));
                if (grid [x-1][y-1] == 2 || grid [x-1][y-1] == 4 || grid [x-1][y-1] == 6 || grid [x-1][y-1] == 8 || grid [x-1][y-1] == 10)
                legalcells.push_back(xytocell(x-1,y-1));
                if (grid [x-1][y+1] == 2 || grid [x-1][y+1] == 4 || grid [x-1][y+1] == 6 || grid [x-1][y+1] == 8 || grid [x-1][y+1] == 10)
                legalcells.push_back(xytocell(x-1,y+1));
            }
        }
        else if (grid[x][y] == 2){
            oldcell = xytocell(x,y);
            if (!hasmoved){
                if (grid [x+1][y] == 0)legalcells.push_back(xytocell(x+1,y));
                if (grid [x+1][y] == 0 && grid [x+2][y] == 0)legalcells.push_back(xytocell(x+2,y));
                if (grid [x+1][y-1] == 1 || grid [x+1][y-1] == 3 || grid [x+1][y-1] == 6 || grid [x+1][y-1] == 8 || grid [x+1][y-1] == 10)
                legalcells.push_back(xytocell(x+1,y-1));
                if (grid [x+1][y+1] == 1 || grid [x+1][y+1] == 4 || grid [x+1][y+1] == 6 || grid [x+1][y+1] == 8 || grid [x+1][y+1] == 10)
                legalcells.push_back(xytocell(x+1,y+1));
            }
            else{
                if (grid [x+1][y] == 0)legalcells.push_back(xytocell(x+1,y));
                if (grid [x+1][y-1] == 1 || grid [x+1][y-1] == 3 || grid [x+1][y-1] == 6 || grid [x+1][y-1] == 8 || grid [x+1][y-1] == 10)
                legalcells.push_back(xytocell(x+1,y-1));
                if (grid [x+1][y+1] == 1 || grid [x+1][y+1] == 4 || grid [x+1][y+1] == 6 || grid [x+1][y+1] == 8 || grid [x+1][y+1] == 10)
                legalcells.push_back(xytocell(x+1,y+1));
            }
        }
    }
}

void pawn::move(short cell, short grid[8][8]){
    if (cellpublic != -1){
        short x, y, tempx, tempy;
        celltoxy(x, y, cell);
        if (!legalcells.empty()){
            auto test = std::find(legalcells.begin(), legalcells.end(),cell);
            if (test != legalcells.end()){
                celltoxy(tempx, tempy, oldcell);
                cellpublic = cell;
                grid[tempx][tempy] = 0;
                if (turn) grid[x][y] = 1;
                if (!turn) grid[x][y] = 2;
                if (tempx == x - 2 || tempx == x + 2 )hasmoved = !hasmoved;
                x = -1;
                y = -1; 
                cellToPos(posx,posy,cellpublic);
                turn = !turn;
                oldcell = -1;
                legalcells.clear();
                return;
            }
        }
    }
}
