#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <3ds.h>
#include <citro2d.h>
#include <map>
#include <fstream>
#include <malloc.h>
#include <dirent.h>
#include <ctype.h>
//my headers
#include <button.h>
#include <helper.h>
#include <picecesClass.hpp>
#include <varhelp.h>

short grid [8][8], movegrid[8][8];
bool turn=true;

void drawFullScreenGrid(short rows, short cols) {
    short screenWidth = 320;
    short screenHeight = 240;

    float cellWidth = (float)screenWidth / cols;
    float cellHeight = (float)screenHeight / rows;

    for (short i = 1; i < cols; i++) {
        float x = i * cellWidth;
        C2D_DrawRectSolid(x, 0, 0.0f, 4, screenHeight, C2D_Color32(0,0,0,255));
    }
    for (short i = 1; i < rows; i++) {
        float y = i * cellHeight;
        C2D_DrawRectSolid(0, y, 0.0f, screenWidth, 4, C2D_Color32(0,0,0,255));
    }
}

void drawChessGrid(){
    drawFullScreenGrid(8,8);
    bool colorturn =true;
    u32 color;
    short xpos=0,ypos=0;
    for (int i=0; i <8 ; i++){
        for (int j=0; j <8 ; j++){
            if (colorturn){
                color = C2D_Color32(237,214,176,255);
            }
            else {
                color = C2D_Color32(184,135,98,255);
            }
            C2D_DrawRectSolid(xpos, ypos, 0.5f, 40, 30, color);
            xpos+=40;
            colorturn = !colorturn;
        }
        colorturn = !colorturn;
        ypos+=30;
        xpos=0;
    }
}

float letterhelpdraw(C2D_Text* g_text){
    float targetWidth = 40.0f;
    float targetHeight = 30.0f;

    float width, height;
    C2D_TextGetDimensions(g_text, 1.0f, 1.0f, &width, &height);

    // fallback in case metrics are zero
    if(width <= 0 || height <= 0) {
        width = 8.0f;   // approximate default width for a single glyph
        height = 8.0f;  // approximate default height
    }

    float scaleX = targetWidth / width;
    float scaleY = targetHeight / height;

    return fminf(scaleX, scaleY);
}


int main(){
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
    pawn pawn1(true, column::E);
    C3D_RenderTarget * top = C2D_CreateScreenTarget(GFX_TOP,GFX_LEFT);
    C3D_RenderTarget * bottom = C2D_CreateScreenTarget(GFX_BOTTOM,GFX_LEFT);
    u32 kDown;
    C2D_TextBuf textBuf = C2D_TextBufNew(4096);
    C2D_Text pawn, knight, bichop, queen, rook, king;
    touchPosition touch;
    C2D_TextParse(&pawn,textBuf,"P");
    C2D_TextOptimize(&pawn);
    short cell=100;
    float pawnScale = 1.0f;//letterhelpdraw(&pawn);
    for (short i=0;i<8;i++){
        for (short j=0;j<8;j++){
            grid[i][j]=0;
        }
    }
    grid[6][4] = 1;//just for test
    while (aptMainLoop()){
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        hidScanInput();
        kDown = hidKeysDown();
        hidTouchRead(&touch);
        C2D_SceneBegin(top);
        C2D_TargetClear(top, C2D_Color32(255,255,255,255));
        C2D_SceneBegin(bottom);
        C2D_TargetClear(bottom, C2D_Color32(255,255,255,255));
        drawChessGrid();
        if (touch.px!=0||touch.py!=0 ){
            cell = checkinputtouch(touch);
            pawn1.checkMovement(cell,grid,movegrid);
        }
        C2D_DrawText(&pawn, C2D_WithColor, pawn1.posx, pawn1.posy, 1.0f, pawnScale, pawnScale, C2D_Color32(255,255,255,255));
        if (kDown & KEY_START) break;
        C3D_FrameEnd(0);
    }
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}