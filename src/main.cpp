#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>

#include "../include/Window/Window.hpp"
#include "../include/Window/InputHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/LogConsole.hpp"
#include "../include/ConfigManager.hpp"
#include "../include/AssetManager.hpp"
#include "../include/Renderer.hpp"

int main() {
	Logger::init();

	// Game window
	Window gameWindow("Project M", 800, 600);
	sf::RenderWindow& window = gameWindow.getRenderWindow();

	InputHandler inputHandler;
	ConfigManager configManager;
	AssetManager assetManager;
	Renderer renderer(window);

	ImGui::SFML::Init(window);
	
	// loads animation config
	try {
		const nlohmann::json& animationConfig = configManager.loadConfig("mageAnimationConfig.json");
		// loads frames
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
		Logger::error("Failed to load animation config " + std::string(e.what()));
	}
	
	// main game loop
	sf::Clock deltaClock;
	bool showConsole = true;
	Logger::info("Game started");
	gameWindow.setEventHandler(&inputHandler);

	while (gameWindow.isOpen()) {
		float deltaTime = deltaClock.restart().asSeconds();

		inputHandler.handleEvents(gameWindow.getRenderWindow());
		ImGui::SFML::Update(gameWindow.getRenderWindow(), deltaClock.restart());

		gameWindow.beginDraw();
		renderer.renderCharacterAnimation(assetManager, "mage", "idle", 0.10f, deltaTime);
		inputHandler.renderConsole();
		ImGui::SFML::Render(gameWindow.getRenderWindow());
		gameWindow.endDraw();
	}

	ImGui::SFML::Shutdown();
	return 0;
}