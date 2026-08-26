//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"

char32_t Bishop::utfRepresentation() {
    // Implementation goes here
    return m_is_white ? U'\u2657' : U'\u265D';
}

char Bishop::latin1Representation() {
    // Implementation goes here
    return m_is_white ? 'B' : 'b';
}

Bishop::Bishop(int x, int y, bool isWhite, ChessBoard* board) : ChessPiece(x, y, isWhite, board) {}

int Bishop::validMove(int to_x, int to_y) {
    // Implementation goes here
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    if (abs(to_x - m_x) != abs(to_y - m_y) || (to_x == m_x && to_y == m_y)) {
        return 0;
    }
    int x_direction = (to_x - m_x) / abs(to_x - m_x);
    int y_direction = (to_y - m_y) / abs(to_y - m_y);
    for (int i = 1; i < abs(to_x - m_x); i++) {
        if (m_board->pieceAt(m_x + i * x_direction, m_y + i * y_direction) != nullptr) {
            return 0;
        }
    }
    if (m_board->pieceAt(to_x, to_y) == nullptr) {
        return 1;
    }
    return (m_board->pieceAt(to_x, to_y)->thisWhite() != m_is_white) ? 2 : 0;
}
