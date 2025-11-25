#include "Polygon.h"

#include <cmath>
#include <stdexcept>

Coordinate::Coordinate() : Coordinate(0.0, 0.0) {}

Coordinate::Coordinate(double xVal, double yVal) : x(xVal), y(yVal) {}

Polygon::Polygon() : _numVertices(0), _vertices(nullptr), _color(sf::Color::White) {}

Polygon::~Polygon() {
    delete[] _vertices;
    _vertices = nullptr;
}

void Polygon::setColor(sf::Color color) {
    _color = color;
}

void Polygon::draw(sf::RenderTarget& window) const {
    if (_numVertices == 0 || _vertices == nullptr) {
        return;
    }

    sf::ConvexShape shape(static_cast<std::size_t>(_numVertices));
    for (short i = 0; i < _numVertices; ++i) {
        shape.setPoint(static_cast<std::size_t>(i), sf::Vector2f(static_cast<float>(_vertices[i].x),
                                                                static_cast<float>(_vertices[i].y)));
    }
    shape.setFillColor(_color);

    window.draw(shape);
}

void Polygon::setCoordinate(int idx, const Coordinate coord) {
    if (idx < 0 || idx >= _numVertices || _vertices == nullptr) {
        throw std::out_of_range("Coordinate index is out of range");
    }

    _vertices[idx] = coord;
}

short Polygon::vertexCount() const {
    return _numVertices;
}

const Coordinate& Polygon::vertex(int idx) const {
    if (idx < 0 || idx >= _numVertices || _vertices == nullptr) {
        throw std::out_of_range("Vertex index is out of range");
    }
    return _vertices[idx];
}

double distanceBetween(const Coordinate& lhs, const Coordinate& rhs) {
    const double deltaX = lhs.x - rhs.x;
    const double deltaY = lhs.y - rhs.y;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}
