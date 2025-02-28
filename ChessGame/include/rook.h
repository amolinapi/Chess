#pragma once
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece 
{

public:

    Rook();

    void move(const Vector2f& pos) override;

private:

    

};

#endif // !ROOK_H