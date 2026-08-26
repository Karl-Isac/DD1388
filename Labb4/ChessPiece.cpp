//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

int ChessPiece::validMove(int to_x, int to_y) {
    // Implementation goes here
    return 0;
}

char32_t ChessPiece::utfRepresentation() {
    // Implementation goes here
    return U'\u0000';
}

char ChessPiece::latin1Representation() {
    // Implementation goes here
    return '.';
}

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
/*:  Initialize members here */: m_x(x), m_y(y), m_is_white(is_white), m_board(board) {
    // or here ...
}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    // Implementation goes here
    return validMove(to_x, to_y) == 2;
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    // Implementation goes here
    return validMove(to_x, to_y) == 1;
}

vector<ChessMove> ChessPiece::capturingMoves() {
    // Implementation goes here
    return vector<ChessMove>();
}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    // Implementation goes here
    return vector<ChessMove>();
}
