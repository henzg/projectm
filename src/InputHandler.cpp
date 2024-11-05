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
		if (event.type == sf::Event::KeyPressed) 
			if(event.key.code == sf::Keyboard::Tilde) {
				showConsole = !showConsole;
				Logger::info("Console log toggled");
			}
			else if (event.key.code == sf::Keyboard::W) {
				Logger::info("W has been pressed");
			}
			else if (event.key.code == sf::Keyboard::A) {
				Logger::info("A has been pressed");
			}
			else if (event.key.code == sf::Keyboard::S) {
				Logger::info("S has been pressed");
			}
			else if (event.key.code == sf::Keyboard::D) {
				Logger::info("D has been pressed");
			}
		// add more event handling logic here
	}
}

void InputHandler::renderConsole() {
	if (showConsole) {
		LogConsole::getInstance().renderConsole(&showConsole);
	}
}