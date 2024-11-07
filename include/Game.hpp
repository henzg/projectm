#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "window/Window.hpp"
#include "AssetManager.hpp"
#include "ConfigManager.hpp"
#include "Renderer.hpp"
#include "Window/InputHandler.hpp"
#include "Logger.hpp"

class Game {
public:
    Game(const std::string& title, int width, int height);
    ~Game();

    // Main function to run the game loop
    void run();

private:
    void loadAssets();
    void processEvents();
    void update(float deltaTime);
    void render(float deltaTime);

    // Game components
    Window gameWindow;
    AssetManager assetManager;
    ConfigManager configManager;
    Renderer renderer;
    InputHandler inputHandler;

    // For delta time calculation
    sf::Clock deltaClock;
};