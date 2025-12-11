// Daniel Vega

#include "BinarySearchTree.hpp"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void buildTree(BinarySearchTree<int>& tree, const std::vector<int>& values) {
    for (const int val : values) {
        tree.insert(val);
    }
}

void printTraversals(BinarySearchTree<int>& tree) {
    std::cout << "In Order:      ";
    tree.printInOrder();
    std::cout << "Pre Order:     ";
    tree.printPreOrder();
    std::cout << "Post Order:    ";
    tree.printPostOrder();
    std::cout << "Breadth Order: ";
    tree.printBreadthOrder();
    std::cout << "Depth Order:   ";
    tree.printDepthOrder();
    std::cout << "By Levels:\n";
    tree.printByLevels();
    std::cout << "Height: " << tree.height() << "\n";
}

std::vector<int> promptValues() {
    int n = 0;
    std::cout << "How many integers to add: ";
    std::cin >> n;
    if (n < 0) {
        n = 0;
    }
    std::vector<int> vals;
    vals.reserve(static_cast<std::size_t>(n));
    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        int v = 0;
        std::cin >> v;
        vals.push_back(v);
    }
    return vals;
}

int main() {
    // Run user-provided tree
    BinarySearchTree<int> userTree;
    std::vector<int> userVals = promptValues();
    buildTree(userTree, userVals);
    printTraversals(userTree);

    // Demonstration trees matching the assignment sequences
    const std::vector<std::vector<int>> demoTrees = {
        {6, 5, 7, 1, 2, 9, 3},
        {5, 1, 9, 7, 6, 3, 2},
        {5, 2, 1, 7, 9, 6, 3}
    };

    for (std::size_t i = 0; i < demoTrees.size(); ++i) {
        std::cout << "\nDemo Tree #" << (i + 1) << ":\n";
        BinarySearchTree<int> tree;
        buildTree(tree, demoTrees[i]);
        printTraversals(tree);
    }

    return 0;
}
