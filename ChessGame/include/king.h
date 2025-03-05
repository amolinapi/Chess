#pragma once
#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece 
{

public:

    King();

    bool canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8]) override;

private:

    
};

#endif // !KING_H