#pragma once
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece 
{

public:

    Bishop();

    bool canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8]) override;

private:

    

};

#endif // !BISHOP_H