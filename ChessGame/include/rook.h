#pragma once
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece 
{

public:

    Rook();

    bool canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8]) override;

private:

    

};

#endif // !ROOK_H