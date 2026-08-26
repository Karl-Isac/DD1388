//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"

Pawn::Pawn(int x, int y, bool isWhite, ChessBoard* board) : ChessPiece(x, y, isWhite, board) {}

// Implement method definitions here
int Pawn::validMove(int to_x, int to_y) {
    // Implementation goes here
    int direction = m_is_white ? -1 : 1; // White pawns move up, black pawns move down
    bool starting_row = (m_is_white && m_y == 6) || (!m_is_white && m_y == 1);

    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }

    if (to_x == m_x) {
        // Moving forward
        if (to_y == m_y + direction) {
            return (m_board->pieceAt(to_x, to_y) == nullptr) ? 1 : 0;
        }
        if (starting_row && to_y == m_y + 2 * direction) {
            return (m_board->pieceAt(to_x, to_y) == nullptr && m_board->pieceAt(to_x, to_y - direction) == nullptr) ? 1 : 0;
        }
    }
    if (to_x == m_x + 1 || to_x == m_x - 1) {
        // Capturing diagonally
        if (to_y == m_y + direction) {
            return (m_board->pieceAt(to_x, to_y) != nullptr && m_board->pieceAt(to_x, to_y)->thisWhite() != m_is_white) ? 2 : 0;
        }
    }

    return 0;
}

char32_t Pawn::utfRepresentation() {
    // Implementation goes here
    return m_is_white ? U'\u2659' : U'\u265F';
}

char Pawn::latin1Representation() {
    // Implementation goes here
    return m_is_white ? 'P' : 'p';
}