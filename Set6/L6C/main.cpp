// Daniel Vega

#include "Maze.hpp"

#include <iostream>
#include <exception>
int main(int argc, char* argv[]) {
    std::string filePath;
    if (argc >= 2) {
        filePath = argv[1];
    } else {
        std::cout << "Enter maze file path: ";
        std::cin >> filePath;
    }

    try {
        Maze maze = loadMaze(filePath);
        std::vector<sf::Vector2i> path = solveMaze(maze);
        if (path.empty()) {
            std::cout << "No path found from S to E.\n";
        } else {
            std::cout << "Path found with " << path.size() << " steps.\n";
        }
        drawMaze(maze, path);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
