#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "List.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <stdexcept>

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
  _size = 0;

  // set head to be a nullptr
  _pHead = nullptr;
  
  // set tail to be a nullptr
  _pTail = nullptr;
  
}

template<typename T>
LinkedList<T>::~LinkedList() {
    // remove each node in the list
    while (_pHead != nullptr) {
        Node* pDel = _pHead;
        _pHead = _pHead->pNext;
        delete pDel;
    }
    _pTail = nullptr;
    _size = 0;
}

template<typename T>
int LinkedList<T>::size() const {
    return _size;
}

template<typename T>
T LinkedList<T>::get(const int POS) const {
    // if POS is out of range, throw std::out_of_range exception
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("invalid access at pos " + std::to_string(POS) +
                                " for size " + std::to_string(_size));
    }
    
    // set current node to head
    Node* pCur = _pHead;
    
    // advance current node to POS
    for (int i = 0; i < POS; ++i) {
        pCur = pCur->pNext;
    }
    
    // return value of current node
    return pCur->value;
}

template<typename T>
void LinkedList<T>::set(const int POS, const T VALUE) {
  // if POS is out of range, throw std::out_of_range exception
  if (POS < 0 || POS >= _size) {
      throw std::out_of_range("invalid set at pos " + std::to_string(POS) +
                              " for size " + std::to_string(_size));
  }

  // set current node to head
  Node* pCur = _pHead;

  // advance current node to POS
  for (int i = 0; i < POS; ++i) {
      pCur = pCur->pNext;
  }

  // set value of current node   
  pCur->value = VALUE;
  
}

template<typename T>
void LinkedList<T>::insert(const int POS, const T VALUE) {
    // if POS is before zero, clamp to zero
    int pos = POS;
    if (pos < 0) {
        pos = 0;
    }
    
    // if POS is after size, clamp to size
    if (pos > _size) {
        pos = _size;
    }
    
    // create pointer to new node
    Node* pNew = new Node();
    
    // set value to be VALUE
    pNew->value = VALUE;
    
    // set previous pointer to nullptr
    pNew->pPrev = nullptr;
    
    // set next pointer to nullptr
    pNew->pNext = nullptr;
    
    // if list is currently empty
    if (_size == 0) {
    
        // set head and tail to new node
        _pHead = pNew;
        _pTail = pNew;
    
    // otherwise
    } else {
    
        // if position is before head
        if (pos == 0) {
    
            // set new node next to be head
            pNew->pNext = _pHead;
    
            // set head previous to be new node
            _pHead->pPrev = pNew;
    
            // set head to be new ndoe
            _pHead = pNew;
    
        // else if position is after tail
        } else if (pos == _size) {
    
            // set new node previous to be tail
            pNew->pPrev = _pTail;
    
            // set tail next to be new node
            _pTail->pNext = pNew;
    
            // set tail to be new ndoe
            _pTail = pNew;
    
        // otherwise
        } else {
    
            // set current node to head
            Node* pCur = _pHead;
    
            // advance current node to pos
            for (int i = 0; i < pos; ++i) {
                pCur = pCur->pNext;
            }
    
            // link new node into current list
            pNew->pPrev = pCur->pPrev;
            pNew->pNext = pCur;
    
            // link current list to new node
            pCur->pPrev->pNext = pNew;
            pCur->pPrev = pNew;
        }
    }
    
    // increment size
    ++_size;
    
}

template<typename T>
void LinkedList<T>::remove(const int POS) {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("remove on empty list");
    }
    
    // if POS is before zero, clamp to zero
    int pos = POS;
    if (pos < 0) {
        pos = 0;
    }
    
    // if POS is after size, clamp to size
    if (pos >= _size) {
        pos = _size - 1;
    }
    
    // if list has one element
    if (_size == 1) {
    
        // set node to delete to head
        Node* pDel = _pHead;
    
        // set head and tail to be nullptr
        _pHead = nullptr;
        _pTail = nullptr;
    
        // delete node
        delete pDel;
    
        // decrement size
        --_size;
        return;
    }

    Node* pDel = nullptr;

    // otherwise
    
        // if deleting head
    if (pos == 0) {
    
            // set node to delete to head
            pDel = _pHead;
    
            // advance head to next
            _pHead = _pHead->pNext;
    
            // set head previous to nullptr
            _pHead->pPrev = nullptr;
    
        // else if deleting tail
    } else if (pos == _size - 1) {
    
            // set node to delete to tail
            pDel = _pTail;
    
            // step tail to previous
            _pTail = _pTail->pPrev;
    
            // set tail next to nullptr
            _pTail->pNext = nullptr;
    
        // otherwise
    } else {
    
            // set current node to head
            Node* pCur = _pHead;
    
            // advance current node to space before position
            for (int i = 0; i < pos - 1; ++i) {
                pCur = pCur->pNext;
            }
    
            // set node to delete to the current node's next node
            pDel = pCur->pNext;
    
            // unlink node to delete
            pCur->pNext = pDel->pNext;
            pDel->pNext->pPrev = pCur;
        }
    
    // delete node
    delete pDel;
    
    // decrement size
    --_size;
    
}

template<typename T>
T LinkedList<T>::min() const {
    // if list is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("min on empty list");
    }
    
    // find minimum value within list
    Node* pCur = _pHead;
    T minVal = pCur->value;
    pCur = pCur->pNext;
    while (pCur != nullptr) {
        if (pCur->value < minVal) {
            minVal = pCur->value;
        }
        pCur = pCur->pNext;
    }
    
    // return min value
    return minVal;
}

template<typename T>
T LinkedList<T>::max() const {
    // if list is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("max on empty list");
    }
    
    // find maxiumum value within list
    Node* pCur = _pHead;
    T maxVal = pCur->value;
    pCur = pCur->pNext;
    while (pCur != nullptr) {
        if (pCur->value > maxVal) {
            maxVal = pCur->value;
        }
        pCur = pCur->pNext;
    }
    
    // return max value
    return maxVal;
}

template<typename T>
int LinkedList<T>::find(const T VALUE) const {
    // search for first occurrence of VALUE
    // hint: start at the beginning and go forward
    Node* pCur = _pHead;
    int idx = 0;
    while (pCur != nullptr) {
        if (pCur->value == VALUE) {
            // return index of first occurrence if found
            return idx;
        }
        pCur = pCur->pNext;
        ++idx;
    }
    
    // otherwise return -1
    return -1;
}

template<typename T>
int LinkedList<T>::rfind(const T VALUE) const {
    // search for last occurrence of VALUE
    // hint: start at the end and go backward
    Node* pCur = _pTail;
    int idx = _size - 1;
    while (pCur != nullptr) {
        if (pCur->value == VALUE) {
            // return index of last occurrence if found
            return idx;
        }
        pCur = pCur->pPrev;
        --idx;
    }

    // otherwise return -1
    return -1;
}

#endif//LINKED_LIST_HPP
