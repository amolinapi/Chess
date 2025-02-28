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

    return 0;
}

int GameLoop::loadFonts()
{
    if (!font.loadFromFile("../data/font/Arial.ttf")) {
        return EXIT_FAILURE;
    }
    text = Text("CHESS GAME", font);
    text.setCharacterSize(40);

    FloatRect textBounds = text.getGlobalBounds();

    float centerX = (windowSizeX - textBounds.width) / 2.0f;

    text.setPosition(centerX,0);
    
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
    loadFonts();

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
        window.get()->draw(text);

        //Update Window
        window->display();
    }
    
    return 0;
}
