#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
    // Get the desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Create the window in fullscreen mode using the desktop resolution
    window.create(desktop, "Rogue Ascent", sf::Style::Fullscreen);

    // Load background image
    if (!backgroundTexture.loadFromFile("sprites/background.png")) {
        std::cerr << "Error loading background image" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);  // Set texture to sprite

    // Adjust background to match resolution
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / textureSize.x,
        static_cast<float>(window.getSize().y) / textureSize.y
    );
}

void Game::run() {
    sf::Clock clock;
    player.setStartPosition(window.getSize());  // Call this during initialization
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        processEvents();

        player.update(deltaTime, window);

        // Render the game and menu
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::Resized) {
            // Adjust the view to maintain the aspect ratio
            sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            window.setView(sf::View(visibleArea));

            // Get the current window size
            sf::Vector2u windowSize = window.getSize();

            // Adjust background scale dynamically
            sf::Vector2u textureSize = backgroundTexture.getSize();
            backgroundSprite.setScale(
                static_cast<float>(windowSize.x) / textureSize.x,
                static_cast<float>(windowSize.y) / textureSize.y
            );

            // Update the player's starting position based on the new window size
            player.setStartPosition(windowSize);
        }
    }
}

void Game::render() {
    window.clear();  // Clear the screen before drawing

    // Draw the background first
    window.draw(backgroundSprite);

    // Render the player
    player.render(window);

    // Display everything that was drawn to the window
    window.display();
}
