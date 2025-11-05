#include "Warehouse.h"
#include "Box.h"
#include <string>
#include <iostream>

template <typename T>
Warehouse<T>::Warehouse() {
    _pItems = new std::vector<T*>;
}

template <typename T>
Warehouse<T>::~Warehouse() {
    while( !_pItems->empty() ) {
        delete _pItems->back();
        _pItems->pop_back();
    }
    delete _pItems;
}

template <typename T>
void Warehouse<T>::store(const T& ITEM) {
    _pItems->push_back( new T(ITEM) );
}

template <typename T>
T& Warehouse<T>::retrieve(const size_t ITEM_POS) const {
    return *(_pItems->at(ITEM_POS));
}

template <typename T>
size_t Warehouse<T>::getNumberOfItems() const {
    return _pItems->size();
}

template <typename T>
char Warehouse<T>::getWarehouseLetter() const {
    return _warehouseLetter;
}

template <typename T>
void Warehouse<T>::setWarehouseLetter(char warehouseLetter) {
    _warehouseLetter = warehouseLetter;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const Warehouse<T>& WH) {
    const size_t NUM_ITEMS = WH.getNumberOfItems();
    os << "Warehouse " << WH.getWarehouseLetter() << " has " << NUM_ITEMS << " items (";
    for(size_t i = 0; i < NUM_ITEMS; i++) {
        os << WH.retrieve(i);
        if(i < NUM_ITEMS - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

template class Warehouse<Box>;
template class Warehouse<std::string>;
template std::ostream& operator<< <Box>(std::ostream&, const Warehouse<Box>&);
template std::ostream& operator<< <std::string>(std::ostream&, const Warehouse<std::string>&);