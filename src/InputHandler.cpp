#include "../include/Window/InputHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/LogConsole.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

InputHandler::InputHandler() : showConsole(false) {}

void InputHandler::handleEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed) {
			window.close();
			Logger::info("Game has closed");
		}

		// toggle console log display
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tilde) {
			showConsole = !showConsole;
			Logger::info("Console log toggled");
		}
		// add more event handling logic here
	}
}

void InputHandler::renderConsole() {
	if (showConsole) {
		LogConsole::getInstance().renderConsole(&showConsole);
	}
}