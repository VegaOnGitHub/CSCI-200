#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

int main() {
    // create a window
    const unsigned int WINDOW_W = 1960;
    const unsigned int WINDOW_H = 1080;
    sf::Vector2u windowSize(WINDOW_W, WINDOW_H);
    sf::RenderWindow window( sf::VideoMode( windowSize ), "ts is Kovaaks </3" );
    window.setFramerateLimit(360); // I have 360hz and I'm lowk tryna get a crazy score on this

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

    };
    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // while the window is open
    bool running = true;
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE

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
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////

        /////////////////////////////////////
        // BEGIN ANIMATION UPDATING HERE

        //  END  ANIMATION UPDATING HERE
        /////////////////////////////////////
    }

    return 0;
}
