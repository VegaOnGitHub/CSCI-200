#include <SFML/Graphics.hpp>
#include "Bubble.h"
#include <iostream>
#include <random>
#include <vector>
#include <optional>
#include <algorithm>
#include <cmath>
#include <string>
#include <functional>

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
    std::uniform_real_distribution<float> speedDist(-5.f, 5.f);
    std::uniform_int_distribution<int> colorDist(0, 255);

    const std::function<float(float, float)> randomNonZeroSpeed = [&](float [[maybe_unused]] low, float [[maybe_unused]] high) -> float {
        float v = 0.f;
        do { v = speedDist(rng); } while (std::abs(v) < 0.05f);
        return v;
    };

    const std::function<Bubble()> makeRandomBubble = [&]() -> Bubble {
        float r = radiusDist(rng);
        float diameter = 2.f * r;

        std::uniform_real_distribution<float> xPos(0.f, WINDOW_W - diameter);
        std::uniform_real_distribution<float> yPos(0.f, WINDOW_H - diameter);

        sf::Vector2f pos{xPos(rng), yPos(rng)};
        sf::Vector2f dir{randomNonZeroSpeed(-5.f, 5.f), randomNonZeroSpeed(5.f, 5.f)};
        sf::Color color(colorDist(rng), colorDist(rng), colorDist(rng));

        return Bubble(r, pos, dir, color);
    };

    std::vector<Bubble> bubbles;
    bubbles.reserve(10);
    for (int i = 0; i < 5; ++i){
        bubbles.push_back(makeRandomBubble());
    }

    int score = 0;
    const float GAME_DURATION_SEC = 10.f;
    float timeRemaining = GAME_DURATION_SEC;
    bool gameActive = true;

    sf::Clock frameClock;
    sf::Clock gameClock;
    sf::Time accumulator = sf::Time::Zero;
    const sf::Time dt = sf::seconds(1.f / 60.f);
    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins
    sf::Font font;
    if (!font.openFromFile("data/arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    sf::Text scoreText(font, "", 22);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});

    sf::Text bubbleCountText(font, "", 22);
    bubbleCountText.setFillColor(sf::Color::White);
    bubbleCountText.setPosition({10.f, 40.f});

    sf::Text timerText(font, "", 22);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({10.f, 70.f});

    const std::function<void()> updateHud = [&]() {
        scoreText.setString("Score: " + std::to_string(score));
        bubbleCountText.setString("Bubbles: " + std::to_string(bubbles.size()));
        int displaySeconds = static_cast<int>(std::ceil(timeRemaining));
        timerText.setString("Time: " + std::to_string(displaySeconds));
    };

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // while the window is open
    bool running = true;
    while( window.isOpen() && running) {
        // clear any existing contents
        window.clear();

        if (gameActive) {
            timeRemaining = std::max(0.f, GAME_DURATION_SEC - gameClock.getElapsedTime().asSeconds());
            if (timeRemaining <= 0.f) {
                timeRemaining = 0.f;
                gameActive = false;
            }
        }
        updateHud();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        for (Bubble& b : bubbles){
            b.draw(window);
        }
        window.draw(scoreText);
        window.draw(bubbleCountText);
        window.draw(timerText);

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
            if (const sf::Event::KeyPressed* key = event->getIf<sf::Event::KeyPressed>()){
                if (key->code == sf::Keyboard::Key::Escape || key->code == sf::Keyboard::Key::Q){
                    window.close();
                }
                if (gameActive && key->code == sf::Keyboard::Key::Space){
                    bubbles.push_back(makeRandomBubble());
                }
            }

            if (const sf::Event::MouseButtonPressed* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
                if(gameActive && mb->button == sf::Mouse::Button::Left){
                    const float mx = static_cast<float>(mb->position.x);
                    const float my = static_cast<float>(mb->position.y);
                    const std::size_t before = bubbles.size();
                    bubbles.erase(
                        std::remove_if(bubbles.begin(), bubbles.end(), [&](const Bubble& b) { return b.checkClicked(mx, my); }),
                        bubbles.end()
                    );
                    score += static_cast<int>(before - bubbles.size());
                }
            }
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////

        /////////////////////////////////////
        // BEGIN ANIMATION UPDATING HERE
        if (gameActive) {
            accumulator += frameClock.restart();
            while (accumulator >= dt){
                for (Bubble& b : bubbles){
                    b.updatePosition(static_cast<float>(WINDOW_H), static_cast<float>(WINDOW_W));
                }
                accumulator -= dt;
            }
        } else {
            frameClock.restart();
            accumulator = sf::Time::Zero;
        }

        //  END  ANIMATION UPDATING HERE
        /////////////////////////////////////
    }

    return 0;
}
