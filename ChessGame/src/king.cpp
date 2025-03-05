#include "king.h"

King::King()
{
    type = Piece::Type::KING;
}

bool King::canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8])
{
    // El rey se mueve una casilla en cualquier dirección (horizontal, vertical, diagonal)
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);

    if (dx > 1 || dy > 1) return false; // El rey solo se mueve una casilla

    // Verificar que no haya una pieza propia en la casilla de destino
    if (grid[endX][endY] && grid[endX][endY]->getColorSide() == this->getColorSide()) {
        return false; // No puede moverse a una casilla ocupada por una pieza del mismo color
    }

    return true;
}



