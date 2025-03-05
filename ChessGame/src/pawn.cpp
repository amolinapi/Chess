#include "pawn.h"

Pawn::Pawn()
{
    type = Piece::Type::PAWN;
}

bool Pawn::canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8])
{
    int direction = (getColorSide() == PieceColor::WHITE) ? -1 : 1; // Blancos suben (-1), negros bajan (+1)

    // Movimiento normal: una casilla adelante sin capturar
    if (startX == endX && startY + direction == endY && !grid[endX][endY]) {
        return true;
    }

    // Primer movimiento: dos casillas adelante si no hay nada en el camino
    if (startX == endX && startY + (2 * direction) == endY && !grid[endX][endY] && !grid[startX][startY + direction]) {
        return (startY == ((getColorSide() == PieceColor::WHITE) ? 6 : 1)); // Solo en primera jugada
    }

    // Captura en diagonal
    if (abs(endX - startX) == 1 && startY + direction == endY && grid[endX][endY]) {
        return true;
    }

    return false;
}



