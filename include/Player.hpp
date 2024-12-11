#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.hpp"

class Player {
public:
    Player();
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void setStartPosition(sf::Vector2u windowSize);
    sf::Vector2f getPosition() const;
    void attack(std::vector<Enemy>& enemies);
    sf::Sprite sprite;

private:
    sf::Texture texture;
    int currentFrame;
    float frameSpeed;
    sf::Clock animationClock;
    float movementSpeed;
    sf::FloatRect collisionBox;
    void updateCollisionBox();
};

#endif