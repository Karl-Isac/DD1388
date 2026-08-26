//
// DD1388 - Lab 4: Losing Chess
//

#include "Rook.h"

char32_t Rook::utfRepresentation() {
    // Implementation goes here
    return m_is_white ? U'\u2656' : U'\u265C';
}

char Rook::latin1Representation() {
    // Implementation goes here
    return m_is_white ? 'R' : 'r';
}

Rook::Rook(int x, int y, bool isWhite, ChessBoard* board) : ChessPiece(x, y, isWhite, board) {}

int Rook::validMove(int to_x, int to_y) {
    // Implementation goes here
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    if (to_x != m_x && to_y != m_y) {
        return 0;
    }

    if (to_x == m_x) {
        if (to_y < m_y) {
            for (int i = m_y - 1; i > to_y; i--) {
                if (m_board->pieceAt(m_x, i) != nullptr) {
                    return 0;
                }
            }
        } else {
            for (int i = m_y + 1; i < to_y; i++) {
                if (m_board->pieceAt(m_x, i) != nullptr) {
                    return 0;
                }
            }
        }
    } else {
        if (to_x < m_x) {
            for (int i = m_x - 1; i > to_x; i--) {
                if (m_board->pieceAt(i, m_y) != nullptr) {
                    return 0;
                }
            }
        } else {
            for (int i = m_x + 1; i < to_x; i++) {
                if (m_board->pieceAt(i, m_y) != nullptr) {
                    return 0;
                }
            }
        }
    }
    if (m_board->pieceAt(to_x, to_y) == nullptr) {
        return 1;
    }
    return (m_board->pieceAt(to_x, to_y)->thisWhite() != m_is_white) ? 2 : 0;
}