// ChessGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "gameloop.h"

int main() {

    GameLoop gl = GameLoop();
    gl.createWindow();
    gl.draw();

    return 0;
}



