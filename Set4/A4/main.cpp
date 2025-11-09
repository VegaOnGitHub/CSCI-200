#include <SFML/Graphics.hpp>
#include "Bubble.h"
#include <iostream>
#include <random>
#include <vector>
#include <optional>
#include <algorithm>
#include <cmath>

int main() {
    // create a window
    const unsigned int WINDOW_W = 600;
    const unsigned int WINDOW_H = 600;
    sf::Vector2u windowSize(WINDOW_W, WINDOW_H);
    sf::RenderWindow window( sf::VideoMode( windowSize ), "ts is Kovaaks </3" );
    window.setFramerateLimit(60); 

    //settings up Mersenne Twister (random)
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> radiusDist(10.f, 50.f);
    std::uniform_real_distribution<float> speedDist(-0.8f, 0.8f);
    std::uniform_int_distribution<int> colorDist(0, 255);

    auto randomNonZeroSpeed = [&](float low, float high) {
        float v = 0.f;
        //ensuring its not near zero so it actually moves
        do { v = speedDist(rng); } while (std::abs(v) < 0.05f);
        return v;
    };

    auto makeRandomBubble = [&]() {
        float r = radiusDist(rng);
        float diameter = 2.f * r;

        std::uniform_real_distribution<float> xPos(0.f, WINDOW_W - diameter);
        std::uniform_real_distribution<float> yPos(0.f, WINDOW_H - diameter);

        sf::Vector2f pos{xPos(rng), yPos(rng)};
        sf::Vector2f dir{randomNonZeroSpeed(-0.8f, 0.8f), randomNonZeroSpeed(-0.8f, 0.8f)};
        sf::Color color(colorDist(rng), colorDist(rng), colorDist(rng));

        return Bubble(r, pos, dir, color);
    };

    std::vector<Bubble> bubbles;
    bubbles.reserve(10);
    for (int i = 0; i < 5; ++i){
        bubbles.push_back(makeRandomBubble());
    }

    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    const sf::Time dt = sf::seconds(1.f / 60.f);
    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // while the window is open
    bool running = true;
    while( window.isOpen() && running) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        for (auto& b : bubbles){
            b.draw(window);
        }

        // place any draw commands here to display in the window

        //  END  DRAWING HERE
        /////////////////////////////////////

        // display the current contents of the window
        window.display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        // check if any events happened since the last time checked
        while( const std::optional event = window.pollEvent() ) {
            // if event type corresponds to pressing window X
            if( event->is<sf::Event::Closed>() ) {
                // tell the window to close
                window.close();
            }
            // check additional event types to handle additional events
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()){
                if (key->code == sf::Keyboard::Key::Escape || key->code == sf::Keyboard::Key::Q){
                    window.close();
                }
            }
        }
        if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////

        /////////////////////////////////////
        // BEGIN ANIMATION UPDATING HERE
        accumulator += clock.restart();
        while (accumulator >= dt){
            for (auto& b : bubbles){
                b.updatePosition(static_cast<float>(WINDOW_H), static_cast<float>(WINDOW_W));
            }
            accumulator -= dt;
        }

        //  END  ANIMATION UPDATING HERE
        /////////////////////////////////////
    }

    return 0;
}
