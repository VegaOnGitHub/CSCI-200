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

Maze loadMaze(const std::string& path);
std::vector<sf::Vector2i> solveMaze(const Maze& maze);
void drawMaze(const Maze& maze, const std::vector<sf::Vector2i>& path);

#endif // MAZE_HPP
