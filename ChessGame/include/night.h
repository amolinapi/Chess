#pragma once
#ifndef NIGHT_H
#define NIGHT_H

#include "piece.h"

class Night : public Piece 
{

public:

    Night();

    void move(const Vector2f& pos) override;

private:

    

};

#endif // !NIGHT_H