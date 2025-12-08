#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "EquilateralTriangle.h"
#include "IsoscelesTriangle.h"
#include "Rhombus.h"
#include "ScaleneTriangle.h"

namespace {
std::unique_ptr<Polygon> createPolygon(char type) {
    switch (type) {
        case 'S':
            return std::make_unique<ScaleneTriangle>();
        case 'I':
            return std::make_unique<IsoscelesTriangle>();
        case 'E':
            return std::make_unique<EquilateralTriangle>();
        case 'R':
            return std::make_unique<Rhombus>();
        default:
            return nullptr;
    }
}

sf::Color colorFromInts(int r, int g, int b) {
    const auto clampComponent = [](int value) -> std::uint8_t {
        return static_cast<std::uint8_t>(std::clamp(value, 0, 255));
    };
    return {clampComponent(r), clampComponent(g), clampComponent(b)};
}
}  // namespace

int main(int argc, char* argv[]) {
    const std::string inputPath = (argc > 1) ? argv[1] : "data/polygons.dat";
    std::ifstream input(inputPath);

    if (!input) {
        std::cerr << "Unable to open input file: " << inputPath << '\n';
        return 1;
    }

    std::vector<std::unique_ptr<Polygon>> polygons;
    std::string rawLine;
    while (std::getline(input, rawLine)) {
        if (rawLine.empty()) {
            continue;
        }

        std::istringstream lineStream(rawLine);
        char typeChar{};
        lineStream >> typeChar;
        typeChar = static_cast<char>(std::toupper(static_cast<unsigned char>(typeChar)));

        auto polygon = createPolygon(typeChar);
        if (!polygon) {
            std::cout << "polygon is invalid - \"" << rawLine << "\"\n";
            continue;
        }

        const short verticesNeeded = polygon->vertexCount();
        bool parsedSuccessfully = true;

        for (short idx = 0; idx < verticesNeeded; ++idx) {
            double x{};
            double y{};
            if (!(lineStream >> x >> y)) {
                parsedSuccessfully = false;
                break;
            }

            try {
                polygon->setCoordinate(idx, Coordinate{x, y});
            } catch (const std::exception&) {
                parsedSuccessfully = false;
                break;
            }
        }

        int r{};
        int g{};
        int b{};
        if (!(lineStream >> r >> g >> b)) {
            parsedSuccessfully = false;
        }

        if (!parsedSuccessfully || !polygon->validate()) {
            std::cout << "polygon is invalid - \"" << rawLine << "\"\n";
            continue;
        }

        polygon->setColor(colorFromInts(r, g, b));
        polygons.push_back(std::move(polygon));
    }

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(640U, 640U)), "Polygon Viewer");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        for (const auto& polygon : polygons) {
            polygon->draw(window);
        }
        window.display();
    }

    return 0;
}
