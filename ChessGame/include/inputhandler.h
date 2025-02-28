#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include "board.h"

class InputHandler
{
public:
    void handleEvent(Event& event, RenderWindow* window, Board& board);

private:

};

#endif // !INPUTHANDLER_H
