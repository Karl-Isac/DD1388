//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"

char32_t Knight::utfRepresentation() {
    // Implementation goes here
    return m_is_white ? U'\u2658' : U'\u265E';
}

char Knight::latin1Representation() {
    // Implementation goes here
    return m_is_white ? 'N' : 'n';
}

Knight::Knight(int x, int y, bool isWhite, ChessBoard* board) : ChessPiece(x, y, isWhite, board) {}

int Knight::validMove(int to_x, int to_y) {
    // Implementation goes here
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    if ((abs(to_x - m_x) == 2 && abs(to_y - m_y) == 1) || (abs(to_x - m_x) == 1 && abs(to_y - m_y) == 2)) {
        if (m_board->pieceAt(to_x, to_y) == nullptr) {
            return 1;
        } else if (m_board->pieceAt(to_x, to_y)->thisWhite() != m_is_white) {
            return 2;
        }
    }
    return 0;
}
