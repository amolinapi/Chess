#include "queen.h"

Queen::Queen()
{
    type = Piece::Type::QUEEN;
}

bool Queen::canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8])
{
    // La reina puede moverse en línea recta o diagonal
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);

    // Verificar si el movimiento es en línea recta o diagonal
    if (dx != 0 && dy != 0 && dx != dy) return false; // No es ni horizontal, vertical, ni diagonal

    // Verificar que el camino está libre (sin piezas bloqueando)
    int stepX = (endX > startX) ? 1 : (endX < startX) ? -1 : 0;
    int stepY = (endY > startY) ? 1 : (endY < startY) ? -1 : 0;

    int x = startX + stepX, y = startY + stepY;
    while (x != endX || y != endY) {
        if (grid[x][y]) return false; // Si hay una pieza en el camino, el movimiento no es válido
        x += stepX;
        y += stepY;
    }

    // Verificar que no haya una pieza propia en la casilla de destino
    if (grid[endX][endY] && grid[endX][endY]->getColorSide() == this->getColorSide()) {
        return false; // No puede moverse a una casilla ocupada por una pieza del mismo color
    }

    return true;
}



