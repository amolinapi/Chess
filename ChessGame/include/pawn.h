#pragma once
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece 
{

public:

    Pawn();

    void move(const Vector2f& pos) override;

private:

    

};

#endif // !PAWN_H