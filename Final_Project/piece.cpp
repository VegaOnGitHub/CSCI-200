#include "piece.h"

#include <cctype>
#include <cmath>

#include "board.h"

namespace chess {

Piece::Piece(bool white) : _isWhite(white) {}

bool Piece::isWhite() const {
    return _isWhite;
}

char Piece::symbol() const {
    const char base = type();
    return _isWhite ? base : static_cast<char>(std::tolower(static_cast<unsigned char>(base)));
}

bool Piece::canAttack(const Board& board, Position start, Position target) const {
    return isValidMove(board, start, target);
}

Pawn::Pawn(bool white) : Piece(white) {}

std::unique_ptr<Piece> Pawn::clone() const {
    return std::make_unique<Pawn>(*this);
}

bool Pawn::isValidMove(const Board& board, Position start, Position end) const {
    const int direction = isWhite() ? -1 : 1;
    Piece* destination = board.pieceAt(end);
    const int rowDiff = end.row - start.row;
    const int colDiff = end.col - start.col;

    if (colDiff == 0) {
        if (destination != nullptr) {
            return false;
        }
        if (rowDiff == direction) {
            return true;
        }
        const int initialRow = isWhite() ? 6 : 1;
        if (start.row == initialRow && rowDiff == 2 * direction) {
            Position mid{start.row + direction, start.col};
            return board.pieceAt(mid) == nullptr;
        }
        return false;
    }

    if (std::abs(colDiff) == 1 && rowDiff == direction) {
        return destination != nullptr && destination->isWhite() != isWhite();
    }
    return false;
}

bool Pawn::canAttack(const Board& board, Position start, Position target) const {
    return isValidMove(board, start, target);
}

char Pawn::type() const {
    return 'P';
}

Knight::Knight(bool white) : Piece(white) {}

std::unique_ptr<Piece> Knight::clone() const {
    return std::make_unique<Knight>(*this);
}

bool Knight::isValidMove(const Board& board, Position start, Position end) const {
    const int rowDiff = std::abs(start.row - end.row);
    const int colDiff = std::abs(start.col - end.col);
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) {
        return false;
    }
    if (Piece* destination = board.pieceAt(end); destination && destination->isWhite() == isWhite()) {
        return false;
    }
    return true;
}

char Knight::type() const {
    return 'N';
}

Bishop::Bishop(bool white) : Piece(white) {}

std::unique_ptr<Piece> Bishop::clone() const {
    return std::make_unique<Bishop>(*this);
}

bool Bishop::isValidMove(const Board& board, Position start, Position end) const {
    if (std::abs(start.row - end.row) != std::abs(start.col - end.col)) {
        return false;
    }
    if (!board.pathClear(start, end)) {
        return false;
    }
    if (Piece* dest = board.pieceAt(end); dest && dest->isWhite() == isWhite()) {
        return false;
    }
    return true;
}

char Bishop::type() const {
    return 'B';
}

Rook::Rook(bool white) : Piece(white) {}

std::unique_ptr<Piece> Rook::clone() const {
    return std::make_unique<Rook>(*this);
}

bool Rook::isValidMove(const Board& board, Position start, Position end) const {
    if (start.row != end.row && start.col != end.col) {
        return false;
    }
    if (!board.pathClear(start, end)) {
        return false;
    }
    if (Piece* dest = board.pieceAt(end); dest && dest->isWhite() == isWhite()) {
        return false;
    }
    return true;
}

char Rook::type() const {
    return 'R';
}

Queen::Queen(bool white) : Piece(white) {}

std::unique_ptr<Piece> Queen::clone() const {
    return std::make_unique<Queen>(*this);
}

bool Queen::isValidMove(const Board& board, Position start, Position end) const {
    const bool sameRow = start.row == end.row;
    const bool sameCol = start.col == end.col;
    const bool diag = std::abs(start.row - end.row) == std::abs(start.col - end.col);
    if (!(sameRow || sameCol || diag)) {
        return false;
    }
    if (!board.pathClear(start, end)) {
        return false;
    }
    if (Piece* dest = board.pieceAt(end); dest && dest->isWhite() == isWhite()) {
        return false;
    }
    return true;
}

char Queen::type() const {
    return 'Q';
}

King::King(bool white) : Piece(white) {}

std::unique_ptr<Piece> King::clone() const {
    return std::make_unique<King>(*this);
}

bool King::isValidMove(const Board& board, Position start, Position end) const {
    (void)board;
    const int rowDiff = std::abs(start.row - end.row);
    const int colDiff = std::abs(start.col - end.col);
    if (rowDiff > 1 || colDiff > 1) {
        return false;
    }
    if (Piece* dest = board.pieceAt(end); dest && dest->isWhite() == isWhite()) {
        return false;
    }
    return true;
}

char King::type() const {
    return 'K';
}

}  // namespace chess
