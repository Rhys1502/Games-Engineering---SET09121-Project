#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Texture& texture, const sf::Vector2u& windowSize, const sf::Vector2f& playerPosition);
    void update(sf::Time deltaTime, const sf::Vector2f& playerPosition);
    void render(sf::RenderWindow& window);
    int health;
    int maxHealth;
    int hitsTaken;

    bool isAlive() const { return alive; }  // Getter for alive

    void takeDamage();
    sf::Sprite getEnemySprite() const {
        return enemySprite;
    }

private:
    sf::Sprite enemySprite;
    sf::IntRect animationFrame;
    float speed = 100.f;
    float animationSpeed = 0.1f;
    float currentAnimationTime = 0.f;
    int currentFrame = 0;
    int totalFrames = 11;
    int textureWidth = 24;
    int textureHeight = 32;
    bool isMoving = false;
    bool alive = true;  // Whether the enemy is alive or not
};

#endif