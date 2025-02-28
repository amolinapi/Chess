#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "piece.h";
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "night.h"
#include "rook.h"
#include "bishop.h"

using namespace sf;

class Board
{
public:

    Board();

    int createBoard();
    void initializePieces();
    Vector2f gridToPixel(int x, int y);
    int createPieces();

    void handleClick(Vector2f mousePos);
    void movePiece(int startX, int startY, int endX, int endY);

    void draw(RenderWindow* window);

private:

    Texture chess_board_texture;
    Sprite chess_board_sprite;

    Texture board_texture;
    Sprite board_sprite;

    std::unique_ptr<Piece> grid[8][8];

    std::map<Piece::Type, Texture> textures;
};

#endif // !BOARD_H