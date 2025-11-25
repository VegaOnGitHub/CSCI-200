#include "Quadrilateral.h"

Quadrilateral::Quadrilateral() {
    _numVertices = 4;
    delete[] _vertices;
    _vertices = new Coordinate[static_cast<std::size_t>(_numVertices)];
}
