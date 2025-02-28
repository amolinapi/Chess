#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Piece
{
public:

    enum class Type
    {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        NIGHT,
        PAWN
    };

    enum class PieceColor 
    {
        WHITE,
        BLACK
    };

    Piece() = default;
    Piece(const Piece&) = delete;
    Piece& operator=(const Piece&) = delete;
    Piece(Piece&&) = default;
    Piece& operator=(Piece&&) = default;
    virtual ~Piece() = default;

    Vector2f getPosition();
    void setPosition(Vector2f position);

    Sprite getSprite();
    void setSprite(Sprite sprite);

    void draw(RenderWindow* window);

    void setTexture(const Texture& texture); 
    void setScale(float x, float y);
    void setColor(PieceColor c);

    Piece::Type getType();
    Piece::PieceColor getColorSide();
    void setColorSide(PieceColor c);

    virtual void move(const Vector2f& pos) = 0;

private:

    Sprite piece_sprite;

protected:
    Piece::PieceColor color;
    Piece::Type type;
};

#endif // !PIECE_H
