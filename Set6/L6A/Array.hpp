#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "List.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <stdexcept>

template<typename T>
class Array final : public IList<T> {
public:
    Array();
    ~Array();

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
    int _size;
    T* _pArray;
};

//---------------------------------------------------------

template<typename T>
Array<T>::Array() {
    // set size to zero
    _size = 0;
    // set array to be a nullptr
    _pArray = nullptr;
}

template<typename T>
Array<T>::~Array() {
    // deallocate current array
    delete[] _pArray;
}

template<typename T>
int Array<T>::size() const { 
    return _size;
}

template<typename T>
T Array<T>::get(const int POS) const {
    // if POS is out of range, throw std::out_of_range exception
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("invalid access at pos " + std::to_string(POS) +
                                " for size " + std::to_string(_size));
    }
    return _pArray[POS];
    // return value at POS within array
}

template<typename T>
void Array<T>::set(const int POS, const T VALUE) {
    // if POS is out of range, throw std::out_of_range exception
    if (_size == 0 || POS < 0 || POS >= _size) {
        throw std::out_of_range("invalid set at pos " + std::to_string(POS) +
                                " for size " + std::to_string(_size));
    }
    
    // set VALUE at POS within array    
    _pArray[POS] = VALUE;

}

template<typename T>
void Array<T>::insert(const int POS, const T VALUE) {
    // if POS is before zero, clamp to zero
    int pos = POS;
    if (pos < 0){
        pos = 0;
    }
    // if POS is after size, clamp to size
    if (pos > _size){
        pos = _size;
    }

    // create new array of size + 1
    T* tempArray = new T[_size + 1];
    // copy elements 0 to POS from old array to new array
    for (int i = 0; i < pos; i++){
        tempArray[i] = _pArray[i];
    }
    // set element at POS in new array to VALUE
    tempArray[pos] = VALUE;
    
    // copy elements POS to size from old array to new array
    for (int i = pos; i < _size; i++){
        tempArray[i + 1] = _pArray[i];
    }
    // delete old array
    delete[] _pArray;
    // set old array to be new array
    _pArray = tempArray;


    // increment size
    ++_size;

}

template<typename T>
void Array<T>::remove(const int POS) {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("remove on empty array");
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

    // create new array of size - 1
    T* tempArray = (_size > 1) ? new T[_size - 1] : nullptr;

    // copy elements from 0 to POS from old array to  new array
    for (int i = 0; i < pos; ++i) {
        tempArray[i] = _pArray[i];
    }

    // copy elements from POS+1 to size from old array to new array
    for (int i = pos + 1; i < _size; ++i) {
        tempArray[i - 1] = _pArray[i];
    }

    // delete old array
    delete[] _pArray;

    // set old array to be new array
    _pArray = tempArray;

    // decrement size
    --_size;

}

template<typename T>
T Array<T>::min() const {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("min on empty array");
    }
    
    // find minimum value within array
    T minVal = _pArray[0];
    for (int i = 1; i < _size; ++i) {
        if (_pArray[i] < minVal) {
            minVal = _pArray[i];
        }
    }
    
    // return min value
    return minVal;
}

template<typename T>
T Array<T>::max() const {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("max on empty array");
    }
    
    // find maximum value within array
    T maxVal = _pArray[0];
    for (int i = 1; i < _size; ++i) {
        if (_pArray[i] > maxVal) {
            maxVal = _pArray[i];
        }
    }
    
    // return max value
    return maxVal;
}

template<typename T>
int Array<T>::find(const T VALUE) const {
    // search for first occurrence of VALUE
    // hint: start at the beginning and go forward
    for (int i = 0; i < _size; ++i) {
        if (_pArray[i] == VALUE) {
            // return index of first occurrence if found
            return i;
        }
    }
    
    // otherwise return -1
    return -1;
}

template<typename T>
int Array<T>::rfind(const T VALUE) const {
    // search for last occurrence of VALUE
    // hint: start at the end and go backward
    for (int i = _size - 1; i >= 0; --i) {
        if (_pArray[i] == VALUE) {
            // return index of last occurrence if found
            return i;
        }
    }

    // otherwise return -1
    return -1;
}

#endif//ARRAY_HPP
