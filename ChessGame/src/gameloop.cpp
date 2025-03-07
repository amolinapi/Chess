#include "gameloop.h"
#include <iostream>

GameLoop::GameLoop()
{
    windowSizeX = 800;
    windowSizeY = 800;
}

GameLoop::GameLoop(int sizeX, int sizeY)
{
    windowSizeX = sizeX;
    windowSizeY = sizeY;
}

int GameLoop::createBoard()
{
    board = Board();

    board.createBoard();
    board.initializePieces();
    board.createPieces();
    board.loadFonts();
    board.loadSounds();

    return 0;
}

int GameLoop::loadMusic()
{
    if (!musica.openFromFile("../data/audio/background.wav")) {
        return EXIT_FAILURE;
    }

    musica.setLoop(true);
    musica.setVolume(5);
    musica.play();
    
    return 0;
}

int GameLoop::createWindow()
{
    window = std::make_unique<RenderWindow>(VideoMode(windowSizeX, windowSizeY), "SFML Test");
    
    return 0;
}

int GameLoop::draw()
{
    createBoard();
    loadMusic(),

    window->setFramerateLimit(60);

    while (window && window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            inputHandler.handleEvent(event,window.get(),board);
        }
        //Clear Screen
        window->clear(Color::Black);

        //Draw
        board.draw(window.get());

        //Update Window
        window->display();
    }
    
    return 0;
}
