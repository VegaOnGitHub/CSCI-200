#include "game.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <utility>

namespace chess {

Game::Game() : _whiteTurn(true), _logFile("game_log.txt") {}

std::optional<Position> Game::parseSquare(const std::string& token) const {
    if (token.size() != 2) {
        return std::nullopt;
    }
    const char file = static_cast<char>(std::tolower(static_cast<unsigned char>(token[0])));
    const char rank = token[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return std::nullopt;
    }
    Position pos;
    pos.col = file - 'a';
    pos.row = 8 - (rank - '0');
    return pos;
}

void Game::logMove(const std::string& move) {
    _moveHistory.push_back(move);
    writeHistoryToFile();
}

void Game::writeHistoryToFile() const {
    std::ofstream out(_logFile);
    for (const auto& entry : _moveHistory) {
        out << entry << '\n';
    }
}

bool Game::loadFromFile(const std::string& filename) {
    std::ifstream input(filename);
    if (!input) {
        return false;
    }
    std::string turnLine;
    if (!std::getline(input, turnLine)) {
        return false;
    }
    if (turnLine == "white") {
        _whiteTurn = true;
    } else if (turnLine == "black") {
        _whiteTurn = false;
    } else {
        return false;
    }
    if (!_board.load(input)) {
        return false;
    }
    std::string historyMarker;
    if (!std::getline(input, historyMarker)) {
        historyMarker.clear();
    }
    _moveHistory.clear();
    std::string moveLine;
    while (std::getline(input, moveLine)) {
        if (!moveLine.empty()) {
            _moveHistory.push_back(moveLine);
        }
    }
    writeHistoryToFile();
    return true;
}

bool Game::saveToFile(const std::string& filename) const {
    std::ofstream output(filename);
    if (!output) {
        return false;
    }
    output << (_whiteTurn ? "white" : "black") << '\n';
    _board.save(output);
    output << "---moves---\n";
    for (const auto& entry : _moveHistory) {
        output << entry << '\n';
    }
    return true;
}

void Game::showHelp() const {
    std::cout << "Commands:\n"
              << "  <from> <to>  - make a move (e.g., e2 e4)\n"
              << "  save <file>  - save current game to file\n"
              << "  load <file>  - load game from file\n"
              << "  history      - print moves so far\n"
              << "  help         - show this message\n"
              << "  quit         - exit the game\n";
}

void Game::printStatus() const {
    std::cout << (_whiteTurn ? "White" : "Black") << " to move.\n";
    if (_board.isCheck(_whiteTurn)) {
        std::cout << "Check!\n";
    }
}

void Game::start() {
    _board.initialize();
    _whiteTurn = true;
    _moveHistory.clear();
    writeHistoryToFile();

    std::cout << "Text Chess\n";
    std::cout << "Load saved game? (y/n): ";
    std::string response;
    std::getline(std::cin, response);
    if (!response.empty() && (response[0] == 'y' || response[0] == 'Y')) {
        std::cout << "Enter filename: ";
        std::string filename;
        std::getline(std::cin, filename);
        if (!loadFromFile(filename)) {
            std::cout << "Failed to load game. Starting new game.\n";
            _board.initialize();
            _whiteTurn = true;
            _moveHistory.clear();
            writeHistoryToFile();
        }
    }

    showHelp();

    bool running = true;
    while (running) {
        _board.display(std::cout);
        printStatus();
        if (_board.isCheckmate(_whiteTurn)) {
            std::cout << (_whiteTurn ? "Black" : "White") << " wins by checkmate!\n";
            break;
        }
        if (_board.isStalemate(_whiteTurn)) {
            std::cout << "Stalemate! It's a draw.\n";
            break;
        }

        std::cout << "Enter command: ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (line.empty()) {
            continue;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd == "quit" || cmd == "exit") {
            std::cout << "Ending game.\n";
            break;
        } else if (cmd == "help") {
            showHelp();
            continue;
        } else if (cmd == "history") {
            for (const auto& entry : _moveHistory) {
                std::cout << entry << '\n';
            }
            continue;
        } else if (cmd == "save") {
            std::string filename;
            iss >> filename;
            if (filename.empty()) {
                std::cout << "Specify a filename.\n";
                continue;
            }
            if (saveToFile(filename)) {
                std::cout << "Game saved to " << filename << '\n';
            } else {
                std::cout << "Failed to save game.\n";
            }
            continue;
        } else if (cmd == "load") {
            std::string filename;
            iss >> filename;
            if (filename.empty()) {
                std::cout << "Specify a filename.\n";
                continue;
            }
            if (loadFromFile(filename)) {
                std::cout << "Game loaded.\n";
            } else {
                std::cout << "Failed to load " << filename << '\n';
            }
            continue;
        } else {
            std::string dest;
            iss >> dest;
            if (dest.empty()) {
                std::cout << "Invalid input. Use format like e2 e4.\n";
                continue;
            }
            auto startPos = parseSquare(cmd);
            auto endPos = parseSquare(dest);
            if (!startPos || !endPos) {
                std::cout << "Invalid square notation.\n";
                continue;
            }
            if (_board.movePiece(*startPos, *endPos, _whiteTurn)) {
                std::ostringstream moveLabel;
                moveLabel << (_whiteTurn ? "White" : "Black") << ": " << cmd << " -> " << dest;
                logMove(moveLabel.str());
                _whiteTurn = !_whiteTurn;
            } else {
                std::cout << "Illegal move.\n";
            }
        }
    }

    std::cout << "Game over. Moves saved to " << _logFile << '\n';
}

}  // namespace chess
