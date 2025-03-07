#include "inputhandler.h"
#include <iostream>

void InputHandler::handleEvent(Event& event, RenderWindow* window, Board& board)
{
    if (event.type == Event::Closed) {
        window->close();
    }

    if (event.type == Event::MouseButtonPressed) {
        Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (event.mouseButton.button == Mouse::Left) {
            board.handleClick(mousePos);
        }
    }
}
