#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"   

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void render();
    void spawnEnemies(const sf::Texture& enemyTexture);
    void showPauseMenu();

    sf::Clock spawnClock;        // Clock for managing spawn time
    sf::Time spawnInterval;      // Interval between enemy spawns
    sf::RenderWindow window;
    sf::Music music;
    sf::Font font;
    sf::Text resumeText;
    sf::Text exitText;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::VideoMode desktop;
    bool isPaused = false;
    int killCount = 0;  // Kill counter
    sf::Text killText;  // Text object to display the kill count
    Player player;  // Player object
    std::vector<Enemy> enemies;  // Vector to store enemies
    sf::Texture enemyTexture;    // Texture for enemies
};

#endif
