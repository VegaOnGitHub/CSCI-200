// Daniel Vega
#include "Array.hpp"
#include "LinkedList.hpp"

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <random>
#include <string>

template<typename T>
void printList(const IList<T>& list) {
    for (int i = 0; i < list.size(); ++i) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << list.get(i);
    }
    std::cout << std::endl;
}

template<typename T>
void fillList(IList<T>& list, const std::initializer_list<T>& values) {
    int pos = 0;
    for (const T& value : values) {
        list.insert(pos++, value);
    }
}

void demoArraySort() {
    Array<int> arr;
    fillList(arr, {4, 3, 8, 1, 5, 9, 7, 2, 6});

    std::cout << "Sorting an array:" << std::endl;
    std::cout << "Initial array: ";
    printList(arr);

    arr.sort();

    std::cout << "Sorted array: ";
    printList(arr);
    std::cout << std::endl;
}

void demoLinkedListSortInts() {
    LinkedList<int> list;
    fillList(list, {4, 3, 8, 1, 5, 9, 7, 2, 6});

    std::cout << "Sorting a Linked List:" << std::endl;
    std::cout << "Initial list: ";
    printList(list);

    list.sort();

    std::cout << "Sorted list: ";
    printList(list);
    std::cout << std::endl;
}

void demoLinkedListSortStrings() {
    LinkedList<std::string> list;
    fillList(list, {std::string("dog"), std::string("cat"), std::string("bird"), std::string("elephant")});

    std::cout << "Sorting a Linked List:" << std::endl;
    std::cout << "Initial list: ";
    printList(list);

    list.sort();

    std::cout << "Sorted list: ";
    printList(list);
    std::cout << std::endl;
}

void populateRandom(IList<int>& list, const int n, const int min, const int max) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    for (int i = 0; i < n; ++i) {
        list.insert(list.size(), dist(gen));
    }
}

void runSearchProgram() {
    int listChoice = 0;
    std::cout << "Choose list implementation (1 - Array, 2 - Linked List): ";
    std::cin >> listChoice;

    IList<int>* pList = nullptr;
    if (listChoice == 1) {
        pList = new Array<int>();
    } else {
        pList = new LinkedList<int>();
    }

    int n = 0;
    int minVal = 0;
    int maxVal = 0;

    std::cout << "How many integers to enter: ";
    std::cin >> n;
    std::cout << "Enter smallest value to generate: ";
    std::cin >> minVal;
    std::cout << "Enter largest value to generate: ";
    std::cin >> maxVal;

    if (maxVal < minVal) {
        std::swap(minVal, maxVal);
    }
    if (n < 0) {
        n = 0;
    }

    populateRandom(*pList, n, minVal, maxVal);

    std::cout << "Unsorted list: ";
    printList(*pList);

    pList->sort();
    std::cout << "Sorted list: ";
    printList(*pList);

    int numTargets = 0;
    std::cout << "How many target values to search for: ";
    std::cin >> numTargets;

    for (int i = 0; i < numTargets; ++i) {
        int target = 0;
        std::cout << "Target #" << i + 1 << ": ";
        std::cin >> target;
        std::cout << pList->search(target) << std::endl;
    }

    delete pList;
}

int main() {
    demoArraySort();
    demoLinkedListSortInts();
    demoLinkedListSortStrings();

    runSearchProgram();
    return 0;
}
