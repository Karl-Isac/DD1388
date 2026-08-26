//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

void ChessBoard::movePiece(ChessMove chess_move) {
    // Implementation goes here
    chess_move.piece->m_x = chess_move.to_x;
    chess_move.piece->m_y = chess_move.to_y;
}

vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    // Implementation goes here
    vector<ChessMove> moves;
    vector<ChessPiece *> pieces = is_white ? m_white_pieces : m_black_pieces;
    for (int i = 0; i < m_state.rows(); i++) {
        for (int j = 0; j < m_state.cols(); j++) {
            for (ChessPiece * piece : pieces) {
                if (piece->capturingMove(j, i)) {
                    ChessMove move;
                    move.from_x = piece->getX();
                    move.from_y = piece->getY();
                    move.to_x = j;
                    move.to_y = i;
                    move.piece = piece;
                    moves.push_back(move);
                }
            }
        }
    }
    return moves;
}

vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    // Implementation goes here
    vector<ChessMove> moves;
    vector<ChessPiece *> pieces = is_white ? m_white_pieces : m_black_pieces;
    for (int i = 0; i < m_state.rows(); i++) {
        for (int j = 0; j < m_state.cols(); j++) {
            for (ChessPiece * piece : pieces) {
                if (piece->nonCapturingMove(j, i)) {
                    ChessMove move;
                    move.from_x = piece->getX();
                    move.from_y = piece->getY();
                    move.to_x = j;
                    move.to_y = i;
                    move.piece = piece;
                    moves.push_back(move);
                }
            }
        }
    }
    return moves;
}

ChessBoard & operator>>(istream & is, ChessBoard & cb) {
    char piece;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++){
            is >> piece;
            switch(piece) {
                case 'R':
                    cb.state(x,y) =
                        make_shared<Rook>(x,y,true,&cb);
                    break;

                case 'r':
                    cb.state(x,y) =
                        make_shared<Rook>(x,y,false,&cb);
                    break;

                case 'N':
                    cb.state(x,y) =
                        make_shared<Knight>(x,y,true,&cb);
                    break;

                case 'n':
                    cb.state(x,y) =
                        make_shared<Knight>(x,y,false,&cb);
                    break;
                case 'B':
                    cb.state(x,y) =
                        make_shared<Bishop>(x,y,true,&cb);
                    break;

                case 'b':
                    cb.state(x,y) =
                        make_shared<Bishop>(x,y,false,&cb);
                    break;
                case 'Q':
                    cb.state(x,y) =
                        make_shared<Queen>(x,y,true,&cb);
                    break;

                case 'q':
                    cb.state(x,y) =
                        make_shared<Queen>(x,y,false,&cb);
                    break;
                case 'K':
                    cb.state(x,y) =
                        make_shared<King>(x,y,true,&cb);
                    break;

                case 'k':
                    cb.state(x,y) =
                        make_shared<King>(x,y,false,&cb);
                    break;
                case 'P':
                    cb.state(x,y) =
                        make_shared<Pawn>(x,y,true,&cb);
                    break;

                case 'p':
                    cb.state(x,y) =
                        make_shared<Pawn>(x,y,false,&cb);
                    break;
                default:
                    cb.state(x,y) = nullptr;
            }
            if (cb.pieceAt(x,y) != nullptr) {
                ChessPiece * piece = cb.pieceAt(x,y);
                if (piece->thisWhite()) {
                    cb.whitePieces().push_back(piece);
                } else {
                    cb.blackPieces().push_back(const_cast<ChessPiece *>(piece));
                }
            }
        }
    }

    return cb;
}

ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++){
                if (cb.pieceAt(x,y) != nullptr) {
                os << cb.pieceAt(x,y)->letter();
            } else {
                os << '.';
            }
        }
        os << "\n";
    }
    return cb;
}

ChessPiece * ChessBoard::pieceAt(int x, int y) const {
    // Implementation goes here
    if (x < 0 || x > 7 || y < 0 || y > 7) {
        return nullptr;
    }
    return m_state(x, y).get();
}