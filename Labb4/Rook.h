//
// DD1388 - Lab 4: Losing Chess
//

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

class Rook : public ChessPiece {
        public:
            char32_t utfRepresentation() override;
            char latin1Representation() override;
            int validMove(int to_x, int to_y) override;
            Rook(int x, int y, bool isWhite, ChessBoard* board);
};


#endif //ROOK_H
