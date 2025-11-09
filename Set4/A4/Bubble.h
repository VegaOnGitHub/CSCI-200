#ifndef BUBBLE_H   
#define BUBBLE_H

#include <SFML/Graphics.hpp>

class Bubble{
    private:
        sf::CircleShape bubble;
        float xDir{0.f};
        float yDir{0.f};
    public:
        Bubble();
        Bubble(float radius, sf::Vector2f pos, sf::Vector2f dir, sf::Color color);
        void draw(sf::RenderWindow& window);
        void updatePosition(float windowW, float windowH);
        bool checkClicked(float mouseX, float mouseY) const;
        sf::Vector2f getPos() const;
        float setRadius() const;
        void setColor(sf::Color RGB);
        void setPosition(sf::Vector2f pos);
        void setRadius(float r);
        void setDirection(sf::Vector2f dir);
        sf::Vector2f getDirection() const;
};

#endif
