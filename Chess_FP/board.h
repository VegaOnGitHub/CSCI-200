#ifndef BOARD_H
#define BOARD_H

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include "piece.h"
#include "position.h"

class Board {
public:
    Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    Board(Board&&) noexcept = default;
    Board& operator=(Board&&) noexcept = default;
    ~Board() = default;

    void initialize();
    void clear();
    void display(std::ostream& os) const;

    bool movePiece(Position start, Position end, bool whiteTurn);
    bool isCheck(bool white) const;
    bool isCheckmate(bool white) const;
    bool isStalemate(bool white) const;

    void save(std::ostream& os) const;
    bool load(std::istream& is);

    std::string squareName(Position pos) const;
    Piece* pieceAt(Position pos) const;
    bool pathClear(Position start, Position end) const;

private:
    std::vector<std::vector<std::unique_ptr<Piece>>> _grid;

    void copyFrom(const Board& other);
    bool inBounds(Position pos) const { return pos.isValid(); }
    bool wouldLeaveKingInCheck(Position start, Position end, bool color) const;
    void executeMove(Position start, Position end);
    Position locateKing(bool white) const;
    bool squareAttacked(Position pos, bool byWhite) const;
    bool hasLegalMove(bool white) const;
    void promotePawnIfNeeded(Position pos);
    static std::unique_ptr<Piece> createPieceFromChar(char symbol);
};

#endif  // BOARD_H
