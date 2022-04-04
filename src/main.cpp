#include <iostream>
#include <SFML/Graphics.hpp>

#include "utils.hpp"

int main()
{
    // Create a clock;
    sf::Clock clock;

    // Create sf::ContextSettings for changing graphic settings.
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    // Define screen resolution.
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;

    // Create the game window object.
    // And enable vertical sync.
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Nonstop Ball", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    // Load the font file from disk.
    // Send message if unsuccessful. 
    sf::Font font;
    if (!font.loadFromFile("res/Roboto-Regular.ttf"))
    {
        utils::errorOutput("[ERROR]: Could NOT load font file. Please be sure the font file is near the program and try again.");
        return -1;
    }

    // Load the texture file from disk.
    // Send message if unsuccessful. 
    sf::Texture texture;
    if (!texture.loadFromFile("res/ball.png"))
    {
        utils::errorOutput("[ERROR]: Could NOT load ball image. Please be sure the ball image file is near the program and try again.");
        return -1;
    }

    // Smooth the texture.
    texture.setSmooth(true);

    // Load the image file from disk.
    // Send message if unsuccessful. 
    sf::Image iconImage;
    if (!iconImage.loadFromFile("res/ball.png"))
    {
        utils::errorOutput("[ERROR]: Could NOT load ball image. Please be sure the ball image file is near the program and try again.");
        return -1;
    }

    // Set window icon.
    sf::Vector2u iconSize = iconImage.getSize();
    window.setIcon(iconSize.x, iconSize.y, iconImage.getPixelsPtr());
    
    // Create the sf::Text object that will display the FPS value.
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(17);
    fpsText.setStyle(sf::Text::Regular);
    fpsText.setString("FPS: " + std::to_string(utils::getFrameRate(clock)));
    fpsText.setFillColor(sf::Color::Black);
    fpsText.setPosition(sf::Vector2f(10.0f, 10.0f));

    // Create the sf::Text object to display the speed value.
    sf::Text speedText;
    speedText.setFont(font);
    speedText.setCharacterSize(17);
    speedText.setStyle(sf::Text::Regular);
    speedText.setString("Speed: ");
    speedText.setFillColor(sf::Color::Black);
    speedText.setPosition(sf::Vector2f(10.0f, 30.0f));

    // Create the sf::Text object that will show the acceleration and deceleration status.
    sf::Text speedingUpText;
    speedingUpText.setFont(font);
    speedingUpText.setCharacterSize(17);
    speedingUpText.setStyle(sf::Text::Regular);
    speedingUpText.setString("Press mouse button to speeding up.");
    speedingUpText.setFillColor(sf::Color::Black);
    speedingUpText.setPosition(sf::Vector2f(10.0f, 50.0f));

    // Create the sf::Text object that indicates exiting the game.
    sf::Text exitInfoText;
    exitInfoText.setFont(font);
    exitInfoText.setCharacterSize(17);
    exitInfoText.setStyle(sf::Text::Regular);
    exitInfoText.setString("Press ESC key to exit the game.");
    exitInfoText.setFillColor(sf::Color::Black);
    exitInfoText.setPosition(sf::Vector2f(10.0f, 70.0f));

    // Create a sf::CircleShape for ball.
    float ballRadius = 32.0f;
    sf::CircleShape ball(ballRadius);

    // Set the texture of ball.
    ball.setTexture(&texture);
    
    // Set ball position and origin.
    ball.setPosition(sf::Vector2f(ballRadius + 10.0f, ballRadius + 40.0f));
    ball.setOrigin(sf::Vector2f(ballRadius, ballRadius));

    // Define motion directions.
    bool movingLeft = false;
    bool movingUp = false;
    bool movingRight = true;
    bool movingDown = true;

    // Define movement speed acceleration value.
    float velocity = 8.0f;
    float accelerate = 0.5f;

    // Define the lowest and highest movement speeds.
    float minVelocity = velocity;
    float maxVelocity = velocity * 100.0f;

    // Define the rotation speed.
    float rotationSpeed = velocity;

    // Define the directions of rotation.
    bool rotatingLeft = false;
    bool rotatingRight = false;

    // Define the variable that specifies the acceleration and deceleration states.
    bool speedingUp = false;

    // Create the game loop.
    while (window.isOpen())
    {
        // Create the event capture loop.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Actions to be taken when pressing any key.
            if (event.type == sf::Event::KeyPressed)
            {
                // Exit the game by pressing the ESC key.
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            // Listen for actions to be taken when clicking the mouse.
            if (event.type == sf::Event::MouseButtonPressed)
            {
                speedingUp = true;
                speedingUpText.setString("Release mouse button to slowing down.");
            }

            // Listen for the actions to be taken when you click and release the mouse.
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                speedingUp = false;
                speedingUpText.setString("Press mouse button to speeding up.");
            }
        }

        // Refresh window and fill white.
        window.clear(sf::Color::White);

        // Get the ball position.
        sf::Vector2f ballPosition = ball.getPosition();

        // If the ball hits the wall while going left, it turns right.
        // If it is going up at this time, it rotate counterclockwise. 
        // If it's going down, it turns clockwise. 
        if (movingLeft)
        {
            ball.move(sf::Vector2f(-velocity, 0.0f));

            if (ballPosition.x - ballRadius <= 0)
            {
                movingLeft = false;
                movingRight = true;

                if (movingUp)
                {
                    rotatingLeft = true;
                    rotatingRight = false;
                }
                else if (movingDown)
                {
                    rotatingLeft = false;
                    rotatingRight = true;
                }
            }
        }

        // If the ball hits the wall while going up, it turns down.
        // If it is going left at this time, it rotate counterclockwise. 
        // If it's going right, it turns clockwise. 
        if (movingUp)
        {
            ball.move(sf::Vector2f(0.0f, -velocity));

            if (ballPosition.y - ballRadius <= 0)
            {
                movingUp = false;
                movingDown = true;

                if (movingLeft)
                {
                    rotatingLeft = false;
                    rotatingRight = true;
                }
                else if (movingRight)
                {
                    rotatingLeft = true;
                    rotatingRight = false;
                }
            }
        }

        // If the ball hits the wall while going right, it turns left.
        // If it is going up at this time, it rotate clockwise. 
        // If it's going down, it turns counterclockwise. 
        if (movingRight)
        {
            ball.move(sf::Vector2f(velocity, 0.0f));

            if (ballPosition.x + ballRadius >= windowWidth)
            {
                movingRight = false;
                movingLeft = true;

                if (movingUp)
                {
                    rotatingLeft = false;
                    rotatingRight = true;
                }
                else if (movingDown)
                {
                    rotatingLeft = true;
                    rotatingRight = false;
                }
            }
        }

        // If the ball hits the wall while going down, it turns up.
        // If it is going left at this time, it rotate counterclockwise. 
        // If it's going right, it turns clockwise. 
        if (movingDown)
        {
            ball.move(sf::Vector2f(0.0f, velocity));

            if (ballPosition.y + ballRadius >= windowHeight)
            {
                movingDown = false;
                movingUp = true;

                if (movingLeft)
                {
                    rotatingLeft = true;
                    rotatingRight = false;
                }
                else if (movingRight)
                {
                    rotatingLeft = false;
                    rotatingRight = true;
                }
            }
        }

        // Rotate the ball at the specified speed.
        if (rotatingLeft)
        {
            ball.rotate(-rotationSpeed);
        }
        else if (rotatingRight)
        {
            ball.rotate(rotationSpeed);
        }

        // Click the mouse to speed up the ball.
        // Slow down when it relesead.
        if (speedingUp && velocity < maxVelocity)
        {
            velocity += accelerate;
        }
        else if (!speedingUp && velocity > minVelocity)
        {
            velocity -= accelerate;
        }

        // Draw ball sprite.
        window.draw(ball);

        // Draw all sf::Text objects.
        window.draw(fpsText);
        window.draw(speedText);
        window.draw(speedingUpText);
        window.draw(exitInfoText);

        // Rewrite FPS text.
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(utils::getFrameRate(clock))));

        // Rewrite speed value text;
        speedText.setString("Speed: " + std::to_string(static_cast<int>(velocity)));

        // Dislay window.
        window.display();
    }

    // Successfully exit the program.
    return 0;
}
