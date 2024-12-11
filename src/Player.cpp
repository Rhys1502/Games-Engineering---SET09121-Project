#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>

Player::Player() {
    // Load the sprite sheet
    if (!texture.loadFromFile("sprites/player.png")) {
        std::cerr << "Error loading player texture!" << std::endl;
    }

    // Set the texture on the sprite
    sprite.setTexture(texture);

    // Set the initial scale for the player sprite
    sprite.setScale(5.f, 5.f);  // Scale the player sprite

    // Initialize animation variables
    currentFrame = 0;
    frameSpeed = 0.2f;  // Frame change interval in seconds

    // Initialize movement speed
    movementSpeed = 200.f;  // Move at 200 pixels per second

    // Set collision box once the sprite is initialized
    updateCollisionBox();  // Update collision box initially
}

void Player::update(sf::Time deltaTime, sf::RenderWindow& window) {
    sf::Vector2f position = sprite.getPosition();  // Get current position

    // Process horizontal movement input (left and right only)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= movementSpeed * deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += movementSpeed * deltaTime.asSeconds();
    }

    // Keep the Y position fixed (no vertical movement)
    position.y = sprite.getPosition().y;  // Ensure Y is fixed based on start position

    // Clamp position to window boundaries horizontally
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    sf::Vector2u windowSize = window.getSize();  // Get current window size

    if (position.x < 0) position.x = 0;
    if (position.x + playerBounds.width > windowSize.x) position.x = windowSize.x - playerBounds.width;

    // Apply the position (no change to Y)
    sprite.setPosition(position);

    // Update the animation frame based on elapsed time
    if (animationClock.getElapsedTime().asSeconds() >= frameSpeed) {
        currentFrame++;
        if (currentFrame >= 2) {  // Assuming 2 frames for walking
            currentFrame = 0;  // Loop back to the first frame
        }

        int frameWidth = 24;  // Width of each frame
        int frameHeight = 24; // Height of each frame
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

        animationClock.restart();
    }

    // Update collision box based on window size
    updateCollisionBox();
}
void Player::updateCollisionBox() {
    // Get the window size directly from the global window size or sprite bounds
    collisionBox = sprite.getGlobalBounds();  // Get global bounds of the sprite
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);  // Draw the player sprite
}
void Player::setStartPosition(sf::Vector2u windowSize) {
    // Get the original sprite texture size (before scaling)
    sf::Vector2u originalSize = texture.getSize();  // Get original texture size

    // Center horizontally based on original texture size
    float startX = windowSize.x / 2.f - originalSize.x / 2.f;

    // Calculate the Y-position to ensure the player is a fixed distance from the bottom
    const float distanceFromBottom = 150.f;  // Adjust as needed
    float startY = windowSize.y - originalSize.y - distanceFromBottom;

    // Debugging: Output window size and original sprite bounds (before scaling)
    std::cout << "Window Size: (" << windowSize.x << ", " << windowSize.y << ")\n";
    std::cout << "Original Sprite Bounds: (" << originalSize.x << ", " << originalSize.y << ")\n";
    std::cout << "Start Position: (" << startX << ", " << startY << ")\n";

    // Set the initial position (once, during initialization)
    sprite.setPosition(startX, startY);  // Set the player's position
}