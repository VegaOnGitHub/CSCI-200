#include <iostream>
#include <cmath>
#include <random>

#include <SFML/Graphics.hpp>

int main() {
	// Variables for creating and moving the sprite
	float spriteX = 100, spriteY = 100;
	sf::Clock programClock;
    sf::Time lastTime = programClock.getElapsedTime();
    const int THRESHOLD = 500;
	std::random_device rd;
    std::mt19937 mt( rd() );
    std::uniform_int_distribution<int> intDist(1, INT_MAX);

    // TODO #1 - Create a 640x640 Window
	sf::Vector2u windowSize(640, 640);
	sf::RenderWindow window(sf::VideoMode(windowSize),"SFML Test");

    // TODO #3 Draw loop
	while (window.isOpen()) {
		window.clear(sf::Color(155,0,255));

        // TODO #6
		sf::CircleShape star;
        star.setPosition( sf::Vector2f(15.f, 15.f) );
        star.setRadius(300.f);
        star.setFillColor( sf::Color(255,165,0) );
        window.draw( star );

        // TODO #7
		sf::RectangleShape rect;
        rect.setSize( sf::Vector2f( 45.f, 150.f ) );
        rect.setPosition( sf::Vector2f(200.f, 150.f) );
        rect.setFillColor( sf::Color(0, 0, 255) );
        window.draw(rect);

		sf::RectangleShape rect2;
        rect2.setSize( sf::Vector2f( 45.f, 150.f) );
        rect2.setPosition( sf::Vector2f(400.f, 150.f) );
        rect2.setFillColor( sf::Color(0, 0, 255) );
        window.draw(rect2);

        // TODO #9: 
		for( float i = 0.f; i <= 3.14f; i += 3.14f/512.0f ) {
            sf::ConvexShape convexShape( 4 );
            convexShape.setPoint( 0, sf::Vector2f( cosf( i )*150.f+320.f,   sinf(i)*150.f+320.f ) );
            convexShape.setPoint( 1, sf::Vector2f( cosf( i )*150.f+320.f+15.f, sinf(i)*150.f+320.f ) );
            convexShape.setPoint( 2, sf::Vector2f( cosf( i )*150.f+320.f+15.f, sinf(i)*150.f+320.f+15.f ) );
            convexShape.setPoint( 3, sf::Vector2f( cosf( i )*150.f+320.f,   sinf(i)*150.f+320.f+15.f ) );
            convexShape.setFillColor( sf::Color( 0, 255, 0 ) );
            window.draw( convexShape );
		}

        // TODO #10 - Load a font and create a text label using the font
		sf::Font myFont;
        if( !myFont.openFromFile( "data/arial.ttf" ) ) {
			std::cerr << "Could not load font" << std::endl;
            return -1;
		}
        sf::Text label( myFont );
        label.setString( "Hello World!" );
        label.setPosition( sf::Vector2f(250.f, 520.f) );
        label.setFillColor( sf::Color::Black );
        window.draw( label );

		// TODO #10 - Create a sprite that moves
		// Load the image as a texture for the sprite
		sf::Texture myTexture;
        if( !myTexture.loadFromFile( "data/bubble.png" ) ) {
            std::cerr << "Could not load image" << std::endl;
            return -2;
        }

		// Create a sprite with the loaded texture
		sf::Sprite mySprite(myTexture);
        mySprite.setScale( sf::Vector2f(0.10f,0.10f) );
        mySprite.setPosition( sf::Vector2f(spriteX, spriteY) );            
        window.draw( mySprite );

		// Cause the sprite to move based on elapsed time
		sf::Time currTime = programClock.getElapsedTime();
        if( (currTime - lastTime).asMilliseconds() > THRESHOLD ) {
            spriteX += (float)(intDist(mt)%10 - 5);
            spriteY += (float)(intDist(mt)%10 - 5);
            lastTime = currTime;
        }

        // TODO #2: Apply any draws to the window
		window.display();

        // TODO #5
		while (const std::optional event = window.pollEvent()) {
			// Check for a window close event
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

			// Check for a key pressed event and if the key pressed is 'Q'
			if ( const sf::Event::KeyPressed *keyPressed = event->getIf<sf::Event::KeyPressed>() ) {
    			if( keyPressed->scancode == sf::Keyboard::Scan::Q ) {
      				window.close();
				}
			}

			// Check if a mouse button was pressed and move the bubble to that location
			if ( const sf::Event::MouseButtonPressed *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>() ) {
				spriteX = (float)mouseButtonPressed->position.x;
                spriteY = (float)mouseButtonPressed->position.y;
			}
		}

    // TODO #4
	}

    return EXIT_SUCCESS;
}