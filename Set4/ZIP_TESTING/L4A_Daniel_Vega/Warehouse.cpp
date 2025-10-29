#include "Warehouse.h"

using namespace std;

Warehouse::Warehouse() {
    _pBoxen = new vector<Box*>;
    _warehouseLetter = '?';
}

Warehouse::Warehouse(const Warehouse& WH) {
    _pBoxen = new vector<Box*>; 
    for (Box* b : *WH._pBoxen) {
        _pBoxen->push_back(new Box(*b));
    }
    _warehouseLetter = WH._warehouseLetter;
}

Warehouse& Warehouse::operator=(const Warehouse& WH) {
    if (this == &WH) return *this; 

    for (Box* b : *_pBoxen) delete b;
    _pBoxen->clear();

    for (Box* b : *WH._pBoxen) {
        _pBoxen->push_back(new Box(*b)); 
    }

    _warehouseLetter = WH._warehouseLetter;
    return *this;
}

Warehouse::~Warehouse() {
    if (_pBoxen) {
        for (Box* b : *_pBoxen)
            delete b;
        delete _pBoxen;
        _pBoxen = nullptr;
    }
}



void Warehouse::storeInBox(const int SIZE) {
    _pBoxen->push_back( new Box(SIZE) );
}

Box* Warehouse::getBox(const size_t BOX_POS) const {
    return _pBoxen->at(BOX_POS);
}

size_t Warehouse::getNumberOfBoxes() const {
    return _pBoxen->size();
}

char Warehouse::getWarehouseLetter() const {
    return _warehouseLetter;
}

void Warehouse::setWarehouseLetter(const char warehouseLetter) {
    _warehouseLetter = warehouseLetter;
}

std::ostream& operator<<(ostream& os, const Warehouse& WH) {
    os << "Warehouse " << WH.getWarehouseLetter() << " has " << WH.getNumberOfBoxes() << " boxes (";
    for(size_t i = 0; i < WH.getNumberOfBoxes(); i++) {
        os << WH.getBox(i)->getBoxSize();
        if(i < WH.getNumberOfBoxes() - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
