#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;

int main() {
    // create a window
    sf::Vector2u windowSize(640, 640);
    sf::RenderWindow window( sf::VideoMode( windowSize ), "SFML Test" );

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // while the window is open
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
