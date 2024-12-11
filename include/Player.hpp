#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(sf::Time deltaTime, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void setStartPosition(sf::Vector2u windowSize);
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;

    int currentFrame;
    float frameSpeed;
    sf::Clock animationClock;
    float movementSpeed;
    sf::FloatRect collisionBox;

    void updateCollisionBox();
};

#endif // PLAYER_HPP