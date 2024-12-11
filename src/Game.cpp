#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() {
    // Get the desktop resolution and store it in the member variable
    desktop = sf::VideoMode::getDesktopMode();

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

    if (!enemyTexture.loadFromFile("sprites/enemy.png")) {
        std::cerr << "Error loading enemy texture!" << std::endl;
    }

    killText.setFont(font);
    killText.setCharacterSize(50);  // Adjust the font size as needed
    killText.setFillColor(sf::Color::White);  // Set the text color

    // Use the member variable `desktop` to set the killText position
    killText.setPosition(desktop.width / 2 - killText.getLocalBounds().width / 2, 10);

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

    // Initialize clock for spawning enemies
    spawnClock.restart();
    spawnInterval = sf::seconds(3);  // Spawn an enemy every 3 seconds
}

void Game::spawnEnemies(const sf::Texture& enemyTexture) {
    // Pass the player's position when spawning the enemy
    enemies.push_back(Enemy(enemyTexture, window.getSize(), player.getPosition()));
}

void Game::run() {
    sf::Clock clock;
    player.setStartPosition(window.getSize());

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();

        if (!isPaused) {
            player.update(deltaTime, window);

            for (auto it = enemies.begin(); it != enemies.end();) {
                it->update(deltaTime, player.getPosition());
                if (!it->isAlive()) {  // Use getter to check if the enemy is alive
                    it = enemies.erase(it);
                    killCount++;
                }
                else {
                    ++it;
                }
            }

            if (spawnClock.getElapsedTime() >= spawnInterval) {
                spawnEnemies(enemyTexture);
                spawnClock.restart();
            }
        }

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
            if (event.key.code == sf::Keyboard::Space) {
                player.attack(enemies);  // Pass the enemies vector when the player attacks
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

    window.draw(backgroundSprite);  // Draw the background first

    // Render the game objects (only if not paused)
    if (!isPaused) {
        player.render(window);  // Render player
        for (auto& enemy : enemies) {
            enemy.render(window);  // Render enemies
        }

        // Update the kill counter text and center it
        killText.setString("Kills: " + std::to_string(killCount));

        // Recalculate the position to center the text based on its new content
        sf::FloatRect killBounds = killText.getLocalBounds();
        killText.setPosition(
            desktop.width / 2 - killBounds.width / 2,  // Center horizontally
            10  // Fixed position for top (you can adjust as needed)
        );

        window.draw(killText);  // Draw the kill counter text
    }
    else {
        // Show the pause menu
        showPauseMenu();
    }

    window.display();  // Display everything that was drawn to the window
}

void Game::showPauseMenu() {
    // Draw the resume and exit options in the center of the screen
    window.draw(resumeText);
    window.draw(exitText);
}
