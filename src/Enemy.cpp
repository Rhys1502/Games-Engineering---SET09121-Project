#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy(const sf::Texture& texture, const sf::Vector2u& windowSize, const sf::Vector2f& playerPosition) {
    enemySprite.setTexture(texture);
    enemySprite.setScale(5.f, 5.f);

    float xPos = windowSize.x;  // Position the enemy on the right side of the window
    float yPos = playerPosition.y;
    enemySprite.setPosition(xPos, yPos);

    maxHealth = 5;
    health = maxHealth;
    hitsTaken = 0;

    animationFrame = sf::IntRect(0, 0, textureWidth, textureHeight);
    enemySprite.setTextureRect(animationFrame);
}

void Enemy::takeDamage() {
    hitsTaken++;
    if (hitsTaken >= maxHealth) {
        alive = false;
        std::cout << "Enemy died!" << std::endl;
    }
}

void Enemy::update(sf::Time deltaTime, const sf::Vector2f& playerPosition) {
    sf::Vector2f direction = playerPosition - enemySprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction.y = 0.f;
        direction /= length;
        enemySprite.move(direction.x * speed * deltaTime.asSeconds(), 0.f);
        isMoving = true;
    }
    else {
        isMoving = false;
    }

    if (isMoving) {
        currentAnimationTime += deltaTime.asSeconds();
        if (currentAnimationTime >= animationSpeed) {
            currentAnimationTime = 0.f;
            currentFrame = (currentFrame + 1) % totalFrames;
            animationFrame.left = currentFrame * textureWidth;
            enemySprite.setTextureRect(animationFrame);
        }
    }
    else {
        currentFrame = 0;
        animationFrame.left = 0;
        enemySprite.setTextureRect(animationFrame);
    }
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(enemySprite);
}