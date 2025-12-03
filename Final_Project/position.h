#ifndef POSITION_H
#define POSITION_H

struct Position {
    int row{};
    int col{};

    bool isValid() const { return row >= 0 && row < 8 && col >= 0 && col < 8; }
};

#endif  // POSITION_H
