#include "rook.h"

Rook::Rook()
{
    type = Piece::Type::ROOK;
}

bool Rook::canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8])
{
    if (startX != endX && startY != endY) return false; // Solo mueve en línea recta

    int dx = (endX > startX) ? 1 : (endX < startX) ? -1 : 0;
    int dy = (endY > startY) ? 1 : (endY < startY) ? -1 : 0;

    for (int x = startX + dx, y = startY + dy; x != endX || y != endY; x += dx, y += dy) {
        if (grid[x][y]) return false; // Si hay una pieza en el camino, no se puede mover
    }

    return true;
}



