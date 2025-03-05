#include "night.h"

Night::Night()
{
    type = Piece::Type::NIGHT;
}

bool Night::canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8])
{
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);

    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2); // Movimiento en "L"
}



