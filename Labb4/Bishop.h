//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
    public:
        int validMove(int to_x, int to_y) override;
        char32_t utfRepresentation() override;
        char latin1Representation() override;

        Bishop(int x, int y, bool isWhite, ChessBoard* board);
};


#endif //BISHOP_H
