#pragma once
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece 
{

public:

    Pawn();

    bool canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8]) override;

private:

    

};

#endif // !PAWN_H