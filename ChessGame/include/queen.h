#pragma once
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece 
{

public:

    Queen();

    bool canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8]) override;

private:

    

};

#endif // !QUEEN_H