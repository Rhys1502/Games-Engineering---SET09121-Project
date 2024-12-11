#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
    // Get the desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Create the window in fullscreen mode using the desktop resolution
    window.create(desktop, "Rogue Ascent", sf::Style::Fullscreen);

    // Load font for the menu (make sure you have a font file available)
    if (!font.loadFromFile("fonts/menuFont.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

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

    // Calculate hard-coded center positions
    float screenWidth = static_cast<float>(desktop.width);
    float screenHeight = static_cast<float>(desktop.height);

    // Set up resume text
    resumeText.setFont(font);
    resumeText.setString("Resume");
    resumeText.setCharacterSize(50);
    resumeText.setFillColor(sf::Color::White);

    // Hard-coded center position for resume text
    sf::FloatRect resumeBounds = resumeText.getGlobalBounds();
    resumeText.setPosition(
        (screenWidth - resumeBounds.width) / 2.f,
        (screenHeight - resumeBounds.height) / 2.f - 50
    );

    // Set up exit text
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(50);
    exitText.setFillColor(sf::Color::White);

    // Hard-coded center position for exit text
    sf::FloatRect exitBounds = exitText.getGlobalBounds();
    exitText.setPosition(
        (screenWidth - exitBounds.width) / 2.f,
        (screenHeight - exitBounds.height) / 2.f + 50
    );
}

void Game::run() {
    sf::Clock clock;
    player.setStartPosition(window.getSize());  // Call this during initialization
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        processEvents();

        if (!isPaused) {
            player.update(deltaTime, window);  // Only update player if not paused
        }

        // Render the game and menu
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // Get mouse position relative to window

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
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused;  // Toggle pause state on Escape key press
            }
        }

        // Handle mouse clicks if paused
        if (isPaused && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Check if the mouse click is on the resume button
                if (resumeText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    isPaused = false;  // Unpause the game
                }

                // Check if the mouse click is on the exit button
                if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();  // Exit the game
                }
            }
        }

        // Highlight menu items based on hover
        if (resumeText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            resumeText.setFillColor(sf::Color::Red);
        }
        else {
            resumeText.setFillColor(sf::Color::White);
        }

        if (exitText.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            exitText.setFillColor(sf::Color::Red);
        }
        else {
            exitText.setFillColor(sf::Color::White);
        }
    }
}

void Game::render() {
    window.clear();  // Clear the screen before drawing

    // Draw the background first
    window.draw(backgroundSprite);

    // Render the player
    if (!isPaused) {
        player.render(window);
    }
    else {
        showPauseMenu();
    }

    // Display everything that was drawn to the window
    window.display();
}

void Game::showPauseMenu() {
    // Draw the resume and exit options in the center of the screen
    window.draw(resumeText);
    window.draw(exitText);
}