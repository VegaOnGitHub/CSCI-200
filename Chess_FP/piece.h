#ifndef PIECE_H
#define PIECE_H

#include <memory>

#include "position.h"

class Board;

class Piece {
public:
    explicit Piece(bool white);
    virtual ~Piece() = default;

    bool isWhite() const;
    char symbol() const;

    virtual bool isValidMove(const Board& board, Position start, Position end) const = 0;
    virtual bool canAttack(const Board& board, Position start, Position target) const;
    virtual std::unique_ptr<Piece> clone() const = 0;

protected:
    virtual char type() const = 0;

private:
    bool _isWhite;
};

class Pawn : public Piece {
public:
    explicit Pawn(bool white);
    std::unique_ptr<Piece> clone() const override;
    bool isValidMove(const Board& board, Position start, Position end) const override;
    bool canAttack(const Board& board, Position start, Position target) const override;

protected:
    char type() const override;
};

class Knight : public Piece {
public:
    explicit Knight(bool white);
    std::unique_ptr<Piece> clone() const override;
    bool isValidMove(const Board& board, Position start, Position end) const override;

protected:
    char type() const override;
};

class Bishop : public Piece {
public:
    explicit Bishop(bool white);
    std::unique_ptr<Piece> clone() const override;
    bool isValidMove(const Board& board, Position start, Position end) const override;

protected:
    char type() const override;
};

class Rook : public Piece {
public:
    explicit Rook(bool white);
    std::unique_ptr<Piece> clone() const override;
    bool isValidMove(const Board& board, Position start, Position end) const override;

protected:
    char type() const override;
};

class Queen : public Piece {
public:
    explicit Queen(bool white);
    std::unique_ptr<Piece> clone() const override;
    bool isValidMove(const Board& board, Position start, Position end) const override;

protected:
    char type() const override;
};

class King : public Piece {
public:
    explicit King(bool white);
    std::unique_ptr<Piece> clone() const override;
    bool isValidMove(const Board& board, Position start, Position end) const override;

protected:
    char type() const override;
};

#endif  // PIECE_H
