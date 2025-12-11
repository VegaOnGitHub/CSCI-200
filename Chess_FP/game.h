#ifndef GAME_H
#define GAME_H

#include <optional>
#include <string>
#include <vector>

#include "board.h"

class Game {
public:
    Game();
    void start();

private:
    Board _board;
    bool _whiteTurn;
    std::vector<std::string> _moveHistory;
    std::string _logFile;

    void logMove(const std::string& move);
    void printStatus() const;
    std::optional<Position> parseSquare(const std::string& token) const;
    void writeHistoryToFile() const;
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    void showHelp() const;
};

#endif  // GAME_H
