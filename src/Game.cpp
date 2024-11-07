#include "Game.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

Game::Game(const std::string& title, int width, int height)
    : gameWindow(title, width, height), renderer(gameWindow.getRenderWindow()) {
    Logger::init();
    ImGui::SFML::Init(gameWindow.getRenderWindow());
    gameWindow.setEventHandler(&inputHandler);

    loadAssets();  // Load configurations and assets
}

Game::~Game() {
    ImGui::SFML::Shutdown();
}

void Game::run() {
    Logger::info("Game started");

    while (gameWindow.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();

        processEvents();      // Handle input events
        update(deltaTime);    // Update game state
        render(deltaTime);    // Render to the window
    }
}

void Game::loadAssets() {
    try {
        // Load animation config
        const nlohmann::json& animationConfig = configManager.loadConfig("mageAnimationConfig.json");

        // Load frames for each animation state
        if (animationConfig.contains("mage")) {
            const auto& mageConfig = animationConfig["mage"];
            for (const auto& [state, stateConfig] : mageConfig.items()) {
                std::string path = stateConfig.value("path", "");
                int frames = stateConfig.value("frames", 1);

                if (!path.empty() && frames > 0) {
                    assetManager.loadAnimationFrames("mage", state, path, frames);
                    Logger::info("Loaded: " + std::to_string(frames) + " frames for mage state: " + state);
                }
            }
        }
        else {
            Logger::error("Mage configuration not found in animation config.");
        }
    }
    catch (const std::exception& e) {
        Logger::error("Failed to load animation config: " + std::string(e.what()));
    }
}

void Game::processEvents() {
    inputHandler.handleEvents(gameWindow.getRenderWindow());
    ImGui::SFML::Update(gameWindow.getRenderWindow(), deltaClock.restart());
}

void Game::update(float deltaTime) {
    // Add any game update logic here if needed
}

void Game::render(float deltaTime) {
    gameWindow.beginDraw();

    // Render the mage character's idle animation at a frame duration of 0.1 seconds (10 FPS)
    renderer.renderCharacterAnimation(assetManager, "mage", "idle", 0.1f, deltaTime);

    inputHandler.renderConsole();
    ImGui::SFML::Render(gameWindow.getRenderWindow());

    gameWindow.endDraw();
}