#pragma once
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece 
{

public:

    Bishop();

    void move(const Vector2f& pos) override;

private:

    

};

#endif // !BISHOP_H