#pragma once
#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "board.h"
#include "inputhandler.h"

using namespace sf;

class GameLoop
{
public:

    GameLoop();
    GameLoop(int sizeX, int sizeY);

    int createBoard();
    int loadMusic();

    int createWindow();
    int draw();

private:

    std::unique_ptr<RenderWindow> window;
    unsigned int windowSizeX;
    unsigned int windowSizeY;
    Board board;
    InputHandler inputHandler;
    Music musica;
};

#endif // !GAMELOOP
