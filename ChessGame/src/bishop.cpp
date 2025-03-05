#include "bishop.h"

Bishop::Bishop()
{
    type = Piece::Type::BISHOP;
}

bool Bishop::canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8])
{
    if (abs(endX - startX) != abs(endY - startY)) return false; // Solo diagonales

    int dx = (endX > startX) ? 1 : -1;
    int dy = (endY > startY) ? 1 : -1;

    for (int x = startX + dx, y = startY + dy; x != endX || y != endY; x += dx, y += dy) {
        if (grid[x][y]) return false; // Si hay una pieza en el camino, no se puede mover
    }

    return true;
}

