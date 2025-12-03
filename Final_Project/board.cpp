#include "board.h"

#include <cctype>
#include <iostream>
#include <sstream>

namespace chess {

Board::Board() : _grid(8) {
    for (auto& row : _grid) {
        row.resize(8);
    }
}

Board::Board(const Board& other) : Board() {
    copyFrom(other);
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

void Board::copyFrom(const Board& other) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            _grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] =
                other._grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)]
                    ? other._grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)]->clone()
                    : nullptr;
        }
    }
}

void Board::clear() {
    for (auto& row : _grid) {
        for (auto& slot : row) {
            slot.reset();
        }
    }
}

Piece* Board::pieceAt(Position pos) const {
    if (!inBounds(pos)) {
        return nullptr;
    }
    return _grid[static_cast<std::size_t>(pos.row)][static_cast<std::size_t>(pos.col)].get();
}

void Board::initialize() {
    clear();
    auto placeBackRank = [this](int row, bool white) {
        _grid[static_cast<std::size_t>(row)][0] = std::make_unique<Rook>(white);
        _grid[static_cast<std::size_t>(row)][1] = std::make_unique<Knight>(white);
        _grid[static_cast<std::size_t>(row)][2] = std::make_unique<Bishop>(white);
        _grid[static_cast<std::size_t>(row)][3] = std::make_unique<Queen>(white);
        _grid[static_cast<std::size_t>(row)][4] = std::make_unique<King>(white);
        _grid[static_cast<std::size_t>(row)][5] = std::make_unique<Bishop>(white);
        _grid[static_cast<std::size_t>(row)][6] = std::make_unique<Knight>(white);
        _grid[static_cast<std::size_t>(row)][7] = std::make_unique<Rook>(white);
    };

    placeBackRank(0, false);
    placeBackRank(7, true);

    for (int col = 0; col < 8; ++col) {
        _grid[1][static_cast<std::size_t>(col)] = std::make_unique<Pawn>(false);
        _grid[6][static_cast<std::size_t>(col)] = std::make_unique<Pawn>(true);
    }
}

void Board::display(std::ostream& os) const {
    os << "   a b c d e f g h\n";
    for (int row = 0; row < 8; ++row) {
        os << (8 - row) << "  ";
        for (int col = 0; col < 8; ++col) {
            if (const Piece* piece = _grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)].get()) {
                os << piece->symbol();
            } else {
                os << '.';
            }
            os << ' ';
        }
        os << (8 - row) << '\n';
    }
    os << "   a b c d e f g h\n";
}

bool Board::pathClear(Position start, Position end) const {
    int dRow = (end.row > start.row) ? 1 : (end.row < start.row ? -1 : 0);
    int dCol = (end.col > start.col) ? 1 : (end.col < start.col ? -1 : 0);
    int curRow = start.row + dRow;
    int curCol = start.col + dCol;

    while (curRow != end.row || curCol != end.col) {
        if (_grid[static_cast<std::size_t>(curRow)][static_cast<std::size_t>(curCol)]) {
            return false;
        }
        curRow += dRow;
        curCol += dCol;
    }
    return true;
}

bool Board::squareAttacked(Position pos, bool byWhite) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position from{row, col};
            Piece* attacker = pieceAt(from);
            if (!attacker || attacker->isWhite() != byWhite) {
                continue;
            }
            if (attacker->canAttack(*this, from, pos)) {
                return true;
            }
        }
    }
    return false;
}

Position Board::locateKing(bool white) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (const Piece* piece = pieceAt({row, col})) {
                if (piece->isWhite() == white && piece->symbol() == (white ? 'K' : 'k')) {
                    return {row, col};
                }
            }
        }
    }
    return {-1, -1};
}

bool Board::isCheck(bool white) const {
    Position kingPos = locateKing(white);
    if (!kingPos.isValid()) {
        return false;
    }
    return squareAttacked(kingPos, !white);
}

bool Board::hasLegalMove(bool white) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position from{row, col};
            Piece* piece = pieceAt(from);
            if (!piece || piece->isWhite() != white) {
                continue;
            }
            for (int targetRow = 0; targetRow < 8; ++targetRow) {
                for (int targetCol = 0; targetCol < 8; ++targetCol) {
                    Position to{targetRow, targetCol};
                    if (from.row == to.row && from.col == to.col) {
                        continue;
                    }
                    Piece* occupant = pieceAt(to);
                    if (occupant && occupant->isWhite() == white) {
                        continue;
                    }
                    if (!piece->isValidMove(*this, from, to)) {
                        continue;
                    }
                    if (!wouldLeaveKingInCheck(from, to, white)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(bool white) const {
    return isCheck(white) && !hasLegalMove(white);
}

bool Board::isStalemate(bool white) const {
    return !isCheck(white) && !hasLegalMove(white);
}

void Board::promotePawnIfNeeded(Position pos) {
    Piece* piece = pieceAt(pos);
    if (!piece) {
        return;
    }
    if (piece->symbol() == 'P' && pos.row == 0) {
        _grid[static_cast<std::size_t>(pos.row)][static_cast<std::size_t>(pos.col)] = std::make_unique<Queen>(true);
    } else if (piece->symbol() == 'p' && pos.row == 7) {
        _grid[static_cast<std::size_t>(pos.row)][static_cast<std::size_t>(pos.col)] = std::make_unique<Queen>(false);
    }
}

void Board::executeMove(Position start, Position end) {
    _grid[static_cast<std::size_t>(end.row)][static_cast<std::size_t>(end.col)] =
        std::move(_grid[static_cast<std::size_t>(start.row)][static_cast<std::size_t>(start.col)]);
    _grid[static_cast<std::size_t>(start.row)][static_cast<std::size_t>(start.col)].reset();
    promotePawnIfNeeded(end);
}

bool Board::wouldLeaveKingInCheck(Position start, Position end, bool color) const {
    Board temp(*this);
    temp.executeMove(start, end);
    return temp.isCheck(color);
}

bool Board::movePiece(Position start, Position end, bool whiteTurn) {
    if (!inBounds(start) || !inBounds(end)) {
        return false;
    }
    Piece* moving = pieceAt(start);
    if (!moving || moving->isWhite() != whiteTurn) {
        return false;
    }
    Piece* target = pieceAt(end);
    if (target && target->isWhite() == whiteTurn) {
        return false;
    }
    if (!moving->isValidMove(*this, start, end)) {
        return false;
    }
    if (wouldLeaveKingInCheck(start, end, whiteTurn)) {
        return false;
    }
    executeMove(start, end);
    return true;
}

void Board::save(std::ostream& os) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (const Piece* piece = pieceAt({row, col})) {
                os << piece->symbol();
            } else {
                os << '.';
            }
        }
        os << '\n';
    }
}

bool Board::load(std::istream& is) {
    clear();
    std::string line;
    for (int row = 0; row < 8; ++row) {
        if (!std::getline(is, line) || line.size() < 8) {
            return false;
        }
        for (int col = 0; col < 8; ++col) {
            const char symbol = line[static_cast<std::size_t>(col)];
            if (symbol == '.') {
                _grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)].reset();
            } else {
                _grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] = createPieceFromChar(symbol);
                if (!_grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)]) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::unique_ptr<Piece> Board::createPieceFromChar(char symbol) {
    const bool isWhite = std::isupper(static_cast<unsigned char>(symbol)) != 0;
    const char base = static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)));
    switch (base) {
        case 'P':
            return std::make_unique<Pawn>(isWhite);
        case 'R':
            return std::make_unique<Rook>(isWhite);
        case 'N':
            return std::make_unique<Knight>(isWhite);
        case 'B':
            return std::make_unique<Bishop>(isWhite);
        case 'Q':
            return std::make_unique<Queen>(isWhite);
        case 'K':
            return std::make_unique<King>(isWhite);
        default:
            return nullptr;
    }
}

std::string Board::squareName(Position pos) const {
    if (!pos.isValid()) {
        return "";
    }
    std::string name;
    name.push_back(static_cast<char>('a' + pos.col));
    name.push_back(static_cast<char>('8' - pos.row));
    return name;
}

}  // namespace chess
