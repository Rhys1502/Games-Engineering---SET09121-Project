#include "Game.hpp"
#include <SFML/Graphics.hpp>

Game::Game() {
    // Initialize game variables
}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "RogueAscent");
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    // Handle input
}

void Game::update() {
    // Update game state
}

void Game::render() {
    // Render the game
}