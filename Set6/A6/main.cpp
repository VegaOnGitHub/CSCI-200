// Daniel Vega

#include "Maze.hpp"

#include <SFML/Graphics.hpp>

#include <exception>
#include <iostream>
#include <string>

SearchMode promptMode() {
    char choice = 'b';
    std::cout << "Choose search method (b = BFS, d = DFS): ";
    std::cin >> choice;
    if (choice == 'd' || choice == 'D') {
        return SearchMode::DFS;
    }
    return SearchMode::BFS;
}

int main(int argc, char* argv[]) {
    std::string filePath;
    if (argc >= 2) {
        filePath = argv[1];
    } else {
        std::cout << "Enter maze file path: ";
        std::cin >> filePath;
    }

    const SearchMode mode = promptMode();

    try {
        Maze maze = loadMaze(filePath);
        SearchResult result = solveMazeAnimated(maze, mode);
        if (result.reachedEnd) {
            std::cout << "Path found with " << result.path.size() << " steps." << std::endl;
        } else {
            std::cout << "No path found from S to E." << std::endl;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
