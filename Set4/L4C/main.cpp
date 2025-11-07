#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

int main() {
    // create a window
    sf::Vector2u windowSize(640, 640);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Golden (kidna...)");

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // Colors
    const sf::Color skyBlue(135, 206, 235);
    const sf::Color grassGreen(76, 153, 88);
    const sf::Color mesaBrown(168, 116, 83);
    const sf::Color mesaShadow(140, 100, 72);
    const sf::Color creekBlue(90, 160, 220);
    const sf::Color sunYellow(255, 223, 0);
    const sf::Color rockGray(110, 110, 120);
    const sf::Color snowWhite(245, 245, 245);
    const sf::Color treeBrown(130, 82, 43);
    const sf::Color treeGreen(34, 139, 34);

    // Background: sky and foreground grass
    sf::RectangleShape sky({640.f, 480.f});
    sky.setFillColor(skyBlue);

    sf::RectangleShape grass({640.f, 160.f});
    grass.setFillColor(grassGreen);
    grass.setPosition({0.f, 480.f});

    // Sun
    sf::CircleShape sun(60.f);
    sun.setFillColor(sunYellow);
    sun.setPosition({40.f, 40.f});

    // Sun rays (rotated rectangles)
    std::vector<sf::RectangleShape> rays;
    {
        const sf::Vector2f c = { sun.getPosition().x + sun.getRadius(),
                                 sun.getPosition().y + sun.getRadius() };
        const float rayLen = 70.f;
        const float rayThk = 10.f;
        for (int i = 0; i < 8; ++i) {
            float ang = static_cast<float>(i) * 45.f;
            sf::RectangleShape r({rayLen, rayThk});
            r.setFillColor(sunYellow);
            r.setOrigin({0.f, rayThk / 2.f});
            r.setRotation(sf::degrees(ang));
            float rad = ang * 3.14159265f / 180.f;
            float sx = c.x + (sun.getRadius() - 2.f) * std::cos(rad);
            float sy = c.y + (sun.getRadius() - 2.f) * std::sin(rad);
            r.setPosition({sx, sy});
            rays.push_back(r);
        }
    }

    // Foothills / Mountains (triangles via CircleShape with 3 points)
    auto makeTriangle = [](float baseWidth, float height) {
        sf::CircleShape tri;
        tri.setPointCount(3);          // triangle
        tri.setRadius(height);         // size
        tri.setOrigin({height, height});
        tri.setRotation(sf::degrees(-90.f));
        tri.setScale({baseWidth / (2.f * height), 1.f});
        return tri;
    };

    // Distant gray Rockies behind mesas
    sf::CircleShape mtBack1 = makeTriangle(520.f, 180.f);
    mtBack1.setFillColor(rockGray);
    mtBack1.setPosition({200.f, 380.f});

    sf::CircleShape mtBack2 = makeTriangle(460.f, 150.f);
    mtBack2.setFillColor(sf::Color(95, 95, 105));
    mtBack2.setPosition({470.f, 400.f});

    sf::CircleShape mtBack3 = makeTriangle(420.f, 140.f);
    mtBack3.setFillColor(sf::Color(100, 100, 110));
    mtBack3.setPosition({70.f, 410.f});

    // Snow caps
    sf::CircleShape snow1 = makeTriangle(140.f, 40.f);
    snow1.setFillColor(snowWhite);
    snow1.setPosition({mtBack1.getPosition().x, mtBack1.getPosition().y - 85.f});

    sf::CircleShape snow2 = makeTriangle(120.f, 34.f);
    snow2.setFillColor(snowWhite);
    snow2.setPosition({mtBack2.getPosition().x, mtBack2.getPosition().y - 72.f});

    sf::CircleShape snow3 = makeTriangle(110.f, 30.f);
    snow3.setFillColor(snowWhite);
    snow3.setPosition({mtBack3.getPosition().x, mtBack3.getPosition().y - 65.f});

    // North & South Table Mountain (flat-topped mesas using rectangles)
    // South Table (right)
    sf::RectangleShape southTableTop({220.f, 22.f});
    southTableTop.setFillColor(mesaBrown);
    southTableTop.setPosition({360.f, 410.f});

    sf::RectangleShape southTableFace({220.f, 90.f});
    southTableFace.setFillColor(mesaShadow);
    southTableFace.setPosition({360.f, 432.f});

    // North Table (left)
    sf::RectangleShape northTableTop({240.f, 28.f});
    northTableTop.setFillColor(mesaBrown);
    northTableTop.setPosition({80.f, 420.f});

    sf::RectangleShape northTableFace({240.f, 95.f});
    northTableFace.setFillColor(mesaShadow);
    northTableFace.setPosition({80.f, 448.f});

    // Foreground hill arcs (big circles partially below horizon)
    sf::CircleShape hillL(220.f); hillL.setFillColor(grassGreen); hillL.setPosition({-120.f, 360.f});
    sf::CircleShape hillR(220.f); hillR.setFillColor(grassGreen); hillR.setPosition({380.f, 370.f});

    // Clear Creek (simple sweeping rectangle, lightly rotated)
    sf::RectangleShape creek({700.f, 28.f});
    creek.setFillColor(creekBlue);
    creek.setOrigin({0.f, 14.f});
    creek.setRotation(sf::degrees(-12.f));
    creek.setPosition({-40.f, 560.f});

    // Clouds (overlapping circles)
    std::vector<sf::CircleShape> cloudPuffs;
    auto addCloud = [&](float x, float y) {
        sf::CircleShape a(26.f); a.setFillColor(sf::Color::White); a.setPosition({x, y});
        sf::CircleShape b(32.f); b.setFillColor(sf::Color::White); b.setPosition({x + 20.f, y - 10.f});
        sf::CircleShape c(22.f); c.setFillColor(sf::Color::White); c.setPosition({x + 58.f, y + 2.f});
        sf::CircleShape d(20.f); d.setFillColor(sf::Color::White); d.setPosition({x + 6.f,  y + 6.f});
        cloudPuffs.push_back(a);
        cloudPuffs.push_back(b);
        cloudPuffs.push_back(c);
        cloudPuffs.push_back(d);
    };
    addCloud(360.f, 90.f);
    addCloud(120.f, 130.f);
    addCloud(460.f, 150.f);

    // Trees
    std::vector<sf::RectangleShape> trunks;
    std::vector<sf::CircleShape> foliage;
    auto addTree = [&](float x, float groundY) {
        sf::RectangleShape trunk({22.f, 88.f});
        trunk.setFillColor(treeBrown);
        trunk.setPosition({x, groundY - 88.f});
        trunks.push_back(trunk);

        sf::CircleShape c1(30.f); c1.setFillColor(treeGreen); c1.setPosition({x - 18.f, groundY - 126.f});
        sf::CircleShape c2(24.f); c2.setFillColor(treeGreen); c2.setPosition({x + 10.f, groundY - 142.f});
        sf::CircleShape c3(26.f); c3.setFillColor(treeGreen); c3.setPosition({x - 2.f,  groundY - 156.f});
        foliage.push_back(c1);
        foliage.push_back(c2);
        foliage.push_back(c3);
    };
    addTree(80.f, 480.f);
    addTree(540.f, 480.f);
    addTree(490.f, 490.f);

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // while the window is open
    while (window.isOpen()) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE

        window.draw(sky);

        // Distant mountains
        window.draw(mtBack1);
        window.draw(mtBack2);
        window.draw(mtBack3);
        window.draw(snow1);
        window.draw(snow2);
        window.draw(snow3);

        // Mesas (Table Mountains)
        window.draw(northTableFace);
        window.draw(northTableTop);
        window.draw(southTableFace);
        window.draw(southTableTop);

        // Foreground hill arcs
        window.draw(hillL);
        window.draw(hillR);

        // Sun and rays
        for (auto& r : rays) window.draw(r);
        window.draw(sun);

        // Clouds
        for (auto& p : cloudPuffs) window.draw(p);

        // Clear Creek
        window.draw(creek);

        // Grass foreground
        window.draw(grass);

        // Trees
        for (auto& t : trunks) window.draw(t);
        for (auto& f : foliage) window.draw(f);

        //  END  DRAWING HERE
        /////////////////////////////////////

        // display the current contents of the window
        window.display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////

        /////////////////////////////////////
        // BEGIN ANIMATION UPDATING HERE

        // No animations were used

        //  END  ANIMATION UPDATING HERE
        /////////////////////////////////////
    }

    return 0;
}
