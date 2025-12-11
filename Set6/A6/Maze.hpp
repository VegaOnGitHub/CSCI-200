// Daniel Vega
#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

struct Maze {
    std::vector<std::string> grid;
    int rows = 0;
    int cols = 0;
    sf::Vector2i start{-1, -1};
    sf::Vector2i end{-1, -1};
};

enum class SearchMode { BFS, DFS };

struct SearchResult {
    std::vector<sf::Vector2i> path;
    bool reachedEnd = false;
    std::vector<sf::Vector2i> visitedOrder;
};

Maze loadMaze(const std::string& path);
SearchResult solveMazeAnimated(const Maze& maze, SearchMode mode);

#endif // MAZE_HPP
