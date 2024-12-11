#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>

Player::Player() {
    if (!texture.loadFromFile("sprites/player.png")) {
        std::cerr << "Error loading player texture!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(5.f, 5.f);  // Scale the player sprite

    currentFrame = 0;
    frameSpeed = 0.2f;  // Frame change interval in seconds
    movementSpeed = 200.f;  // Movement speed
    updateCollisionBox();  // Update collision box
}

void Player::update(sf::Time deltaTime, sf::RenderWindow& window) {
    sf::Vector2f position = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= movementSpeed * deltaTime.asSeconds();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += movementSpeed * deltaTime.asSeconds();
    }

    position.y = sprite.getPosition().y;  // Ensure Y stays fixed

    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    sf::Vector2u windowSize = window.getSize();

    if (position.x < 0) position.x = 0;
    if (position.x + playerBounds.width > windowSize.x) position.x = windowSize.x - playerBounds.width;

    sprite.setPosition(position);

    if (animationClock.getElapsedTime().asSeconds() >= frameSpeed) {
        currentFrame++;
        if (currentFrame >= 2) currentFrame = 0;
        int frameWidth = 24, frameHeight = 24;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

        animationClock.restart();
    }

    updateCollisionBox();
}

void Player::updateCollisionBox() {
    collisionBox = sprite.getGlobalBounds();  // Update the collision box
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);  // Draw player sprite
}

void Player::setStartPosition(sf::Vector2u windowSize) {
    sf::Vector2u originalSize = texture.getSize();
    float startX = windowSize.x / 2.f - originalSize.x / 2.f;
    const float distanceFromBottom = 150.f;
    float startY = windowSize.y - originalSize.y - distanceFromBottom;
    sprite.setPosition(startX, startY);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}