#ifndef POLYGON_H
#define POLYGON_H

#include <SFML/Graphics.hpp>

#include <cstddef>

struct Coordinate {
    Coordinate();
    Coordinate(double xVal, double yVal);

    double x;
    double y;
};

class Polygon {
public:
    Polygon();
    virtual ~Polygon();

    void setColor(sf::Color color);
    void draw(sf::RenderTarget& window) const;
    void setCoordinate(int idx, const Coordinate coord);

    short vertexCount() const;

    virtual bool validate() const = 0;

protected:
    short _numVertices;
    Coordinate* _vertices;

    const Coordinate& vertex(int idx) const;

private:
    sf::Color _color;
};

double distanceBetween(const Coordinate& lhs, const Coordinate& rhs);

#endif  // POLYGON_H
