#include "Piece.h"

Piece::Piece(bool color) :_color(color) {}
Piece::~Piece(){}

bool Piece::getColor() const
{
    return _color;
}
