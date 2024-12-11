#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp" // Assuming you have a Player class

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void render();
    void spawnEnemies(const sf::Texture& enemyTexture);
    void showPauseMenu();
    void togglePause();

    sf::RenderWindow window;
    sf::Font font;
    sf::Text resumeText;
    sf::Text exitText;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    bool isPaused = false;

    Player player;  // Assuming you have a Player class
};

#endif // GAME_HPP