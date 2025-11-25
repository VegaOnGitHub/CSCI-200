#include "Triangle.h"

Triangle::Triangle() {
    _numVertices = 3;
    delete[] _vertices;
    _vertices = new Coordinate[static_cast<std::size_t>(_numVertices)];
}
