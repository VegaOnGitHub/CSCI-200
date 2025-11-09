#include "Bubble.h"

Bubble::Bubble() {
        bubble.setRadius(20.f);
        bubble.setFillColor (sf::Color::White);
        bubble.setPosition ({100.f, 100.f});
        xDir = 0.4f;
        yDir = 0.6f;
}

Bubble::Bubble(float radius, sf::Vector2f pos, sf::Vector2f dir, sf::Color color) {
    bubble.setRadius(radius);
    bubble.setFillColor(color);
    bubble.setPosition(pos);
    xDir = dir.x;
    yDir = dir.y;
};

void Bubble::draw(sf::RenderWindow& window) {
    window.draw(bubble);
}

void Bubble::updatePosition(float windowW, float windowH) {
    sf::Vector2f pos = bubble.getPosition();
    pos.x += xDir;
    pos.y += yDir;
    bubble.setPosition(pos);
    
    float r = bubble.getRadius();
    float diameter = 2.f * r;

    if (pos.x + diameter > windowW) {
        bubble.setPosition({pos.x - xDir, pos.y});
        xDir = -xDir;
    }

    pos = bubble.getPosition();
    if (pos.y + diameter > windowH) {
        bubble.setPosition({pos.x, pos.y - yDir});
        yDir =  -yDir;
    }

    pos = bubble.getPosition();
    if (pos.x < 0.f) {
        bubble.setPosition({pos.x - xDir, pos.y});
        xDir = -xDir;
    }

    pos = bubble.getPosition();
    if (pos.y < 0.f) {
        bubble.setPosition({pos.x, pos.y - yDir});
        yDir = -yDir;
    }
}

bool Bubble::checkClicked(float mouseX, float mouseY) const {
    sf::Vector2f pos = bubble.getPosition();
    float r = bubble.getRadius();
    float cx = pos.x + r;
    float cy = pos.y + r;

    float dx = mouseX - cx;
    float dy = mouseY - cy;
    float dist2 = dx*dx + dy*dy;
    return dist2 <= r*r;
}

sf::Vector2f Bubble::getPosition() const {
    return bubble.getPosition();
}

float Bubble::getRadius() const {
    return bubble.getRadius();
}

void Bubble::setColor(sf::Color RBG) {
    bubble.setFillColor(RBG);
}

void Bubble::setDirection(sf::Vector2f dir){
    xDir = dir.x;
    yDir = dir.y;
}

sf::Vector2f Bubble::getDirection() const {
    return {xDir, yDir};
}