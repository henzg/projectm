#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>

#include "../include/Window/Window.hpp"
#include "../include/Window/InputHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/LogConsole.hpp"
#include "../include/ConfigManager.hpp"

int main() {

	Window gameWindow("Project M", 800, 600);
	InputHandler inputHandler;
	Logger::init();
	ConfigManager configManager;
	ImGui::SFML::Init(gameWindow.getRenderWindow());
	
	try {
		const nlohmann::json& characterConfig = configManager.loadConfig("test.json");
		Logger::info("Test config loaded successfully.");

		// check if character defaults and npc keys are presetn
		if (characterConfig.contains("character_defaults") && characterConfig["character_defaults"].contains("npc")) {
			// access npc default config
			const auto& npcDefaults = characterConfig["character_defaults"]["npc"];

			for (const auto& [key, value] : npcDefaults.items()) {
				Logger::info("NPC " + key + ": " + value.dump());
			}
		}
		else {
			Logger::error("NPC Config not found in 'character_defaults'.");
		}
	} catch (const std::exception& e) {
		Logger::error("Failed to load config: " + std::string(e.what()));
	}
	
	sf::Clock deltaClock;
	bool showConsole = true;

	Logger::info("Game started");

	gameWindow.setEventHandler(&inputHandler);

	while (gameWindow.isOpen()) {
		inputHandler.handleEvents(gameWindow.getRenderWindow());
		ImGui::SFML::Update(gameWindow.getRenderWindow(), deltaClock.restart());

		gameWindow.beginDraw();
		//LogConsole::getInstance().renderConsole(&showConsole);
		inputHandler.renderConsole();
		ImGui::SFML::Render(gameWindow.getRenderWindow());
		gameWindow.endDraw();
	}

	ImGui::SFML::Shutdown();
	return 0;
}