#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    // Constructor
    Player();

    // Update method for handling movement, animation, and collision
    void update(sf::Time deltaTime, sf::RenderWindow& window);

    // Render method to draw the player on the window
    void render(sf::RenderWindow& window);

    // Set the starting position of the player based on the window size
    void setStartPosition(sf::Vector2u windowSize);

private:
    // Sprite representing the player
    sf::Sprite sprite;

    // Texture for the player sprite
    sf::Texture texture;

    // Animation variables
    int currentFrame;
    float frameSpeed;
    sf::Clock animationClock;

    // Movement speed
    float movementSpeed;

    // Collision box for the player
    sf::FloatRect collisionBox;

    // Update the collision box based on the sprite's position
    void updateCollisionBox();
};

#endif // PLAYER_HPP
