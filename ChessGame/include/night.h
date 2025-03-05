#pragma once
#ifndef NIGHT_H
#define NIGHT_H

#include "piece.h"

class Night : public Piece 
{

public:

    Night();

    bool canMoveTo(int startX, int startY, int endX, int endY, std::unique_ptr<Piece> grid[8][8]) override;

private:

    

};

#endif // !NIGHT_H