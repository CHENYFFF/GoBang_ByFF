#include "Piece.h"


Piece::Piece(void)
{
}

Piece::Piece(QPoint pos,bool isblk)
{
    position = pos;
    isblack = isblk;
}


Piece::~Piece(void)
{
}
