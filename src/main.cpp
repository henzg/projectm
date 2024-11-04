#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>

#include "../include/Window/Window.hpp"
#include "../include/Window/InputHandler.hpp"
#include "../include/Logger.hpp"

#include "../include/LogConsole.hpp"

int main() {

	Window gameWindow("Project M", 800, 600);
	InputHandler inputHandler;

	Logger::init();

	ImGui::SFML::Init(gameWindow.getRenderWindow());
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