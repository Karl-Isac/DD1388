//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
        int validMove(int to_x, int to_y) override;
        char32_t utfRepresentation() override;
        char latin1Representation() override;

        Knight(int x, int y, bool isWhite, ChessBoard* board);
};


#endif //KNIGHT_H
