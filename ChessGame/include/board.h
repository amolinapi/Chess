#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    int loadSounds();
    int loadFonts();
    int createBoard();
    void initializePieces();
    Vector2f gridToPixel(int x, int y);
    int createPieces();

    void handleClick(Vector2f mousePos);
    void movePiece(int startX, int startY, int endX, int endY);

    void resetGame();

    void draw(RenderWindow* window);

private:

    Texture chess_board_texture;
    Sprite chess_board_sprite;

    Texture board_texture;
    Sprite board_sprite;

    Texture valid_cell_texture;
    Sprite valid_cell_sprite;

    Texture kill_cell_texture;
    Sprite kill_cell_sprite;

    std::unique_ptr<Piece> grid[8][8];

    std::map<Piece::Type, Texture> textures;
    std::map<Piece::Type, Texture> texturesBlack;
    std::pair<int, int> selectedPiece = { -1, -1 };
    std::vector<std::pair<int, int>> moveHints;
    std::vector<std::pair<int, int>> killHints;

    Piece::PieceColor turn;
    Font font;
    Text title;
    Text turnText;

    SoundBuffer moveBuffer;
    SoundBuffer captureBuffer;
    SoundBuffer winBuffer;
    Sound moveSound;
    Sound captureSound;
    Sound winSound;
};

#endif // !BOARD_H