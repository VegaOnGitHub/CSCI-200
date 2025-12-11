// Daniel Vega

#include "Maze.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <optional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <thread>
#include <utility>

namespace {
const int CELL_SIZE = 15;
const sf::Color COLOR_WALL = sf::Color::Black;
const sf::Color COLOR_OPEN = sf::Color::White;
const sf::Color COLOR_VISITED = sf::Color::Magenta;
const sf::Color COLOR_FRONTIER = sf::Color(0, 0, 255);
const sf::Color COLOR_START = sf::Color::Green;
const sf::Color COLOR_END = sf::Color::Red;
const sf::Color COLOR_PATH = sf::Color::Yellow;
const int FRAME_DELAY_MS = 50; // 20 FPS

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
    for (const sf::Vector2i& d : DELTAS) {
        sf::Vector2i next{cell.x + d.x, cell.y + d.y};
        if (next.x >= 0 && next.x < cols && next.y >= 0 && next.y < rows) {
            result.push_back(next);
        }
    }
    return result;
}

sf::Color colorForCell(const char ch,
                       const bool onPath,
                       const bool visited,
                       const bool inFrontier) {
    if (ch == 'S') {
        return COLOR_START;
    }
    if (ch == 'E') {
        return COLOR_END;
    }
    if (onPath) {
        return COLOR_PATH;
    }
    if (visited) {
        return COLOR_VISITED;
    }
    if (inFrontier) {
        return COLOR_FRONTIER;
    }
    if (ch == '#') {
        return COLOR_WALL;
    }
    return COLOR_OPEN;
}

void drawFrame(sf::RenderWindow& window,
               const Maze& maze,
               const std::vector<std::vector<bool>>& visited,
               const std::vector<std::vector<bool>>& frontierMask,
               const std::vector<std::vector<bool>>& pathMask) {
    window.clear(sf::Color::White);
    for (int r = 0; r < maze.rows; ++r) {
        for (int c = 0; c < maze.cols; ++c) {
            const bool onPath = pathMask[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];
            const bool wasVisited = visited[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];
            const bool isFrontier = frontierMask[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];
            sf::RectangleShape cellShape(
                sf::Vector2f(static_cast<float>(CELL_SIZE),
                             static_cast<float>(CELL_SIZE)));
            cellShape.setPosition(sf::Vector2f(
                static_cast<float>(c * CELL_SIZE),
                static_cast<float>(r * CELL_SIZE)));
            cellShape.setFillColor(colorForCell(
                maze.grid[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)],
                onPath,
                wasVisited,
                isFrontier));
            cellShape.setOutlineThickness(0);
            window.draw(cellShape);
        }
    }
    window.display();
}

void sleepFrame() {
    sf::sleep(sf::milliseconds(FRAME_DELAY_MS));
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

SearchResult solveMazeAnimated(const Maze& maze, SearchMode mode) {
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(
            static_cast<unsigned int>(maze.cols * CELL_SIZE),
            static_cast<unsigned int>(maze.rows * CELL_SIZE))),
        "Maze Solver");

    std::vector<std::vector<bool>> visited(
        static_cast<std::size_t>(maze.rows),
        std::vector<bool>(static_cast<std::size_t>(maze.cols), false));
    std::vector<std::vector<bool>> frontierMask(
        static_cast<std::size_t>(maze.rows),
        std::vector<bool>(static_cast<std::size_t>(maze.cols), false));
    std::vector<std::vector<sf::Vector2i>> parent(
        static_cast<std::size_t>(maze.rows),
        std::vector<sf::Vector2i>(static_cast<std::size_t>(maze.cols), {-1, -1}));

    std::deque<sf::Vector2i> frontier;
    frontier.push_back(maze.start);
    frontierMask[static_cast<std::size_t>(maze.start.y)][static_cast<std::size_t>(maze.start.x)] = true;

    SearchResult result{};
    bool searchComplete = false;

    std::vector<std::vector<bool>> pathMask(
        static_cast<std::size_t>(maze.rows),
        std::vector<bool>(static_cast<std::size_t>(maze.cols), false));

    while (window.isOpen()) {
        while (true) {
            std::optional<sf::Event> event = window.pollEvent();
            if (!event) {
                break;
            }
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (event->is<sf::Event::KeyPressed>()) {
                const sf::Event::KeyPressed* keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent != nullptr &&
                    (keyEvent->scancode == sf::Keyboard::Scan::Escape ||
                     keyEvent->scancode == sf::Keyboard::Scan::Q)) {
                    window.close();
                }
            }
        }

        if (!searchComplete && !frontier.empty()) {
            sf::Vector2i cur;
            if (mode == SearchMode::BFS) {
                cur = frontier.front();
                frontier.pop_front();
            } else {
                cur = frontier.back();
                frontier.pop_back();
            }
            frontierMask[static_cast<std::size_t>(cur.y)][static_cast<std::size_t>(cur.x)] = false;

            if (!visited[static_cast<std::size_t>(cur.y)][static_cast<std::size_t>(cur.x)]) {
                visited[static_cast<std::size_t>(cur.y)][static_cast<std::size_t>(cur.x)] = true;
                result.visitedOrder.push_back(cur);
                if (cur == maze.end) {
                    // Found end; mark frontier empty to halt
                    frontier.clear();
                } else {
                    for (const sf::Vector2i& nxt : neighbors(cur, maze.rows, maze.cols)) {
                        if (visited[static_cast<std::size_t>(nxt.y)][static_cast<std::size_t>(nxt.x)]) {
                            continue;
                        }
                        if (frontierMask[static_cast<std::size_t>(nxt.y)][static_cast<std::size_t>(nxt.x)]) {
                            continue;
                        }
                        const char cellVal = maze.grid[static_cast<std::size_t>(nxt.y)]
                                                     [static_cast<std::size_t>(nxt.x)];
                        if (cellVal == '#') {
                            continue;
                        }
                        frontierMask[static_cast<std::size_t>(nxt.y)][static_cast<std::size_t>(nxt.x)] = true;
                        parent[static_cast<std::size_t>(nxt.y)][static_cast<std::size_t>(nxt.x)] = cur;
                        frontier.push_back(nxt);
                    }
                }
            }
        }

        if (!searchComplete && frontier.empty()) {
            searchComplete = true;
            if (visited[static_cast<std::size_t>(maze.end.y)][static_cast<std::size_t>(maze.end.x)]) {
                sf::Vector2i cur = maze.end;
                while (cur.x != -1) {
                    pathMask[static_cast<std::size_t>(cur.y)][static_cast<std::size_t>(cur.x)] = true;
                    result.path.push_back(cur);
                    if (cur == maze.start) {
                        break;
                    }
                    cur = parent[static_cast<std::size_t>(cur.y)][static_cast<std::size_t>(cur.x)];
                }
                std::reverse(result.path.begin(), result.path.end());
                result.reachedEnd = true;
            }
        }

        drawFrame(window, maze, visited, frontierMask, pathMask);
        sleepFrame();
    }

    return result;
}
