//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"

// Implement method definitions here

int King::validMove(int to_x, int to_y) {
    // Implementation goes here
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    if (abs(to_x - m_x) > 1 || abs(to_y - m_y) > 1 || (to_x == m_x && to_y == m_y)) {
        return 0;
    }
    if (m_board->pieceAt(to_x, to_y) == nullptr) {
        return 1;
    }
    else {
        return (m_board->pieceAt(to_x, to_y)->thisWhite() != m_is_white) ? 2 : 0;
    }
}

char32_t King::utfRepresentation() {
    // Implementation goes here
    return m_is_white ? U'\u2654' : U'\u265A';
}

char King::latin1Representation() {
    // Implementation goes here
    return m_is_white ? 'K' : 'k';
}

King::King(int x, int y, bool isWhite, ChessBoard* board) : ChessPiece(x, y, isWhite, board) {}
