#pragma once
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece 
{

public:

    Queen();

    void move(const Vector2f& pos) override;

private:

    

};

#endif // !QUEEN_H