#include <button.h>
#include <3ds.h>
#include <citro2d.h>
short checkinputtouch(touchPosition touch){
    short cellWidth  = 320 / 8; 
    short cellHeight = 240 / 8; 

    short col, row;


    col = touch.px / cellWidth;
    row = touch.py / cellHeight;

    if (col > 7) col = 7;
    if (row > 7) row = 7;

    return row * 8 + col;

}