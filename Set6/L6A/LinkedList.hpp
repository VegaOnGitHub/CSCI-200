#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "List.hpp"

#include <exception>
#include <iostream>
#include <string>

template<typename T>
class LinkedList final : public IList<T> {
public:
    LinkedList();
    ~LinkedList();

    int size() const override;
    T get(const int POS) const override;
    void set(const int POS, const T VALUE) override;
    void insert(const int POS, const T VALUE) override;
    void remove(const int POS) override;
    T min() const override;
    T max() const override;
    int find(const T VALUE) const override;
    int rfind(const T VALUE) const override;

private: 
    struct Node {
        T value;
        Node* pNext;
        Node* pPrev;
    };

    Node* _pHead;
    Node* _pTail;
    int _size;
};

//---------------------------------------------------------

template<typename T>
LinkedList<T>::LinkedList() {
  // set size to zero

  // set head to be a nullptr
  
  // set tail to be a nullptr
  
}

template<typename T>
LinkedList<T>::~LinkedList() {
    // remove each node in the list
    
}

template<typename T>
int LinkedList<T>::size() const {
    return _size;
}

template<typename T>
T LinkedList<T>::get(const int POS) const {
    // if POS is out of range, throw std::out_of_range exception
    
    // set current node to head
    
    // advance current node to POS
    
    // return value of current node
    return T();
}

template<typename T>
void LinkedList<T>::set(const int POS, const T VALUE) {
  // if POS is out of range, throw std::out_of_range exception

  // set current node to head

  // advance current node to POS

  // set value of current node   
  
}

template<typename T>
void LinkedList<T>::insert(const int POS, const T VALUE) {
    // if POS is before zero, clamp to zero
    
    // if POS is after size, clamp to size
    
    // create pointer to new node
    
    // set value to be VALUE
    
    // set previous pointer to nullptr
    
    // set next pointer to nullptr
    
    // if list is currently empty
    
        // set head and tail to new node
    
    // otherwise
    
        // if position is before head
    
            // set new node next to be head
    
            // set head previous to be new node
    
            // set head to be new ndoe
    
        // else if position is after tail
    
            // set new node previous to be tail
    
            // set tail next to be new node
    
            // set tail to be new ndoe
    
        // otherwise
    
            // set current node to head
    
            // advance current node to pos
    
            // link new node into current list
    
            // link current list to new node
    
    // increment size
    
}

template<typename T>
void LinkedList<T>::remove(const int POS) {
    // if array is empty, throw std::out_of_range exception
    
    // if POS is before zero, clamp to zero
    
    // if POS is after size, clamp to size
    
    // if list has one element
    
        // set node to delete to head
    
        // set head and tail to be nullptr
    
    // otherwise
    
        // if deleting head
    
            // set node to delete to head
    
            // advance head to next
    
            // set head previous to nullptr
    
        // else if deleting tail
    
            // set node to delete to tail
    
            // step tail to previous
    
            // set tail next to nullptr
    
        // otherwise
    
            // set current node to head
    
            // advance current node to space before position
    
            // set node to delete to the current node's next node
    
            // unlink node to delete
    
    // delete node
    
    // decrement size
    
}

template<typename T>
T LinkedList<T>::min() const {
    // if list is empty, throw std::out_of_range exception
    
    // find minimum value within list
    
    // return min value
    return T();
}

template<typename T>
T LinkedList<T>::max() const {
    // if list is empty, throw std::out_of_range exception
    
    // find maxiumum value within list
    
    // return max value
    return T();
}

template<typename T>
int LinkedList<T>::find(const T VALUE) const {
    // search for first occurrence of VALUE
    // hint: start at the beginning and go forward
    
    // return index of first occurrence if found
    
    // otherwise return -1
    return -1;
}

template<typename T>
int LinkedList<T>::rfind(const T VALUE) const {
    // search for last occurrence of VALUE
    // hint: start at the end and go backward

    // return index of last occurrence if found

    // otherwise return -1
    return -1;
}

#endif//LINKED_LIST_HPP