// Daniel Vega

#include "Maze.hpp"

#include <algorithm>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <utility>

namespace {
const int CELL_SIZE = 15;

sf::Vector2i promptForSizeOrThrow(const std::string& path, std::ifstream& inFile) {
    int r = 0;
    int c = 0;
    if (!(inFile >> r >> c)) {
        throw std::runtime_error("Failed to read maze dimensions from " + path);
    }
    if (r < 3 || r > 102 || c < 4 || c > 102) {
        throw std::runtime_error("Maze dimensions out of bounds in " + path);
    }
    return {c, r};
}

std::vector<sf::Vector2i> neighbors(const sf::Vector2i& cell, const int rows, const int cols) {
    static const std::vector<sf::Vector2i> DELTAS{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<sf::Vector2i> result;
    for (const auto& d : DELTAS) {
        sf::Vector2i next{cell.x + d.x, cell.y + d.y};
        if (next.x >= 0 && next.x < cols && next.y >= 0 && next.y < rows) {
            result.push_back(next);
        }
    }
    return result;
}

sf::Color colorForCell(const char ch, const bool onPath) {
    if (ch == 'S') {
        return sf::Color::Green;
    }
    if (ch == 'E') {
        return sf::Color::Red;
    }
    if (ch == '#') {
        return sf::Color::Black;
    }
    if (onPath) {
        return sf::Color(100, 149, 237);
    }
    return sf::Color::White;
}
} // namespace

Maze loadMaze(const std::string& path) {
    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        throw std::runtime_error("Could not open maze file: " + path);
    }

    const sf::Vector2i dims = promptForSizeOrThrow(path, inFile);
    const int rows = dims.y;
    const int cols = dims.x;

    Maze maze;
    maze.grid.resize(static_cast<std::size_t>(rows));
    maze.rows = rows;
    maze.cols = cols;

    std::string line;
    std::getline(inFile, line); // consume remainder of first line
    for (int r = 0; r < rows; ++r) {
        std::getline(inFile, line);
        if (static_cast<int>(line.size()) != cols) {
            throw std::runtime_error("Maze row length mismatch on row " + std::to_string(r));
        }
        for (int c = 0; c < cols; ++c) {
            if (line[static_cast<std::size_t>(c)] == 'S') {
                maze.start = {c, r};
            } else if (line[static_cast<std::size_t>(c)] == 'E') {
                maze.end = {c, r};
            }
        }
        maze.grid[static_cast<std::size_t>(r)] = std::move(line);
    }

    if (maze.start.x < 0 || maze.end.x < 0) {
        throw std::runtime_error("Maze missing start or end point");
    }

    return maze;
}

std::vector<sf::Vector2i> solveMaze(const Maze& maze) {
    std::vector<std::vector<bool>> visited(
        static_cast<std::size_t>(maze.rows),
        std::vector<bool>(static_cast<std::size_t>(maze.cols), false));
    std::vector<std::vector<sf::Vector2i>> parent(
        static_cast<std::size_t>(maze.rows),
        std::vector<sf::Vector2i>(static_cast<std::size_t>(maze.cols), {-1, -1}));

    std::queue<sf::Vector2i> q;
    q.push(maze.start);
    visited[static_cast<std::size_t>(maze.start.y)][static_cast<std::size_t>(maze.start.x)] = true;

    while (!q.empty()) {
        sf::Vector2i cur = q.front();
        q.pop();
        if (cur == maze.end) {
            break;
        }

        for (const auto& next : neighbors(cur, maze.rows, maze.cols)) {
            if (visited[static_cast<std::size_t>(next.y)][static_cast<std::size_t>(next.x)]) {
                continue;
            }
            const char cellVal = maze.grid[static_cast<std::size_t>(next.y)]
                                         [static_cast<std::size_t>(next.x)];
            if (cellVal == '#') {
                continue;
            }
            visited[static_cast<std::size_t>(next.y)][static_cast<std::size_t>(next.x)] = true;
            parent[static_cast<std::size_t>(next.y)][static_cast<std::size_t>(next.x)] = cur;
            q.push(next);
        }
    }

    if (!visited[static_cast<std::size_t>(maze.end.y)][static_cast<std::size_t>(maze.end.x)]) {
        return {};
    }

    std::vector<sf::Vector2i> path;
    sf::Vector2i cur = maze.end;
    while (cur.x != -1) {
        path.push_back(cur);
        cur = parent[static_cast<std::size_t>(cur.y)][static_cast<std::size_t>(cur.x)];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void drawMaze(const Maze& maze, const std::vector<sf::Vector2i>& path) {
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>(maze.cols * CELL_SIZE),
            static_cast<unsigned int>(maze.rows * CELL_SIZE))),
        "Maze Visualizer");

    std::vector<std::vector<bool>> pathMask(
        static_cast<std::size_t>(maze.rows),
        std::vector<bool>(static_cast<std::size_t>(maze.cols), false));
    for (const auto& pos : path) {
        pathMask[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)] = true;
    }

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (int r = 0; r < maze.rows; ++r) {
            for (int c = 0; c < maze.cols; ++c) {
                sf::RectangleShape cellShape(
                    sf::Vector2f(static_cast<float>(CELL_SIZE),
                                 static_cast<float>(CELL_SIZE)));
                cellShape.setPosition(sf::Vector2f(
                    static_cast<float>(c * CELL_SIZE),
                    static_cast<float>(r * CELL_SIZE)));
                cellShape.setFillColor(
                    colorForCell(maze.grid[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)],
                                 pathMask[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)]));
                cellShape.setOutlineThickness(0);
                window.draw(cellShape);
            }
        }
        window.display();
    }
}
