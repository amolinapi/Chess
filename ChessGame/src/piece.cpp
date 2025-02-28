#include "piece.h"

Vector2f Piece::getPosition()
{
    return piece_sprite.getPosition();
}

void Piece::setPosition(Vector2f position)
{
    piece_sprite.setPosition(position.x, position.y);
}

Sprite Piece::getSprite()
{
    return piece_sprite;
}

void Piece::setSprite(Sprite sprite)
{
    piece_sprite = sprite;
}

void Piece::draw(RenderWindow* window)
{
    if (window) {
        window->draw(piece_sprite);
    }
}

void Piece::setTexture(const Texture& texture)
{
    piece_sprite.setTexture(texture);
}

void Piece::setScale(float x, float y)
{
    piece_sprite.setScale(x,y);
}

void Piece::setColor(PieceColor c)
{
    switch (c)
    {
    case Piece::PieceColor::WHITE:
        piece_sprite.setColor(Color::White);
        break;
    case Piece::PieceColor::BLACK:
        piece_sprite.setColor(Color::Black);
        break;
    default:
        break;
    }
}

Piece::Type Piece::getType()
{
    return type;
}

Piece::PieceColor Piece::getColorSide()
{
    return color;
}

void Piece::setColorSide(PieceColor c)
{
    color = c;
}
