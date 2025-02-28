#pragma once
#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece 
{

public:

    King();

    void move(const Vector2f& pos) override;

private:

    
};

#endif // !KING_H