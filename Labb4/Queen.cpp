//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

char32_t Queen::utfRepresentation() {
    // Implementation goes here
    return m_is_white ? U'\u2655' : U'\u265B';
}

char Queen::latin1Representation() {
    // Implementation goes here
    return m_is_white ? 'Q' : 'q';
}

Queen::Queen(int x, int y, bool isWhite, ChessBoard* board) : ChessPiece(x, y, isWhite, board) {}

int Queen::validMove(int to_x, int to_y) {
    // Implementation goes here
    if (to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
        return 0;
    }
    if (to_x == m_x && to_y == m_y) {
        return 0;
    }
    Rook rook(m_x, m_y, m_is_white, m_board);
    Bishop bishop(m_x, m_y, m_is_white, m_board);
    int rook_move = rook.validMove(to_x, to_y);
    int bishop_move = bishop.validMove(to_x, to_y);
    if (rook_move == 0 && bishop_move == 0) {
        return 0;
    }
    if (rook_move == 2 || bishop_move == 2) {
        return 2;
    }
    return 1;
}