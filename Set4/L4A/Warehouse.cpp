#include "Warehouse.h"

using namespace std;

Warehouse::Warehouse() {
    _pBoxen = new vector<Box*>;
    _warehouseLetter = '?';
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
