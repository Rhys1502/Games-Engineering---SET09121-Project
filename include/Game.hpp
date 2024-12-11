#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Game {
public:
    Game();  // Constructor
    void run();  // Main game loop

private:
    void processEvents();  // Process events like key presses
    void render();  // Render game elements

    sf::RenderWindow window;
    Player player;  // Player object for the game
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif
