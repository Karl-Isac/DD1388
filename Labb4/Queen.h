//
// DD1388 - Lab 4: Losing Chess
//

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece {
        public:
                int validMove(int to_x, int to_y) override;
                char32_t utfRepresentation() override;
                char latin1Representation() override;

                Queen(int x, int y, bool isWhite, ChessBoard* board);
};


#endif //QUEEN_H
