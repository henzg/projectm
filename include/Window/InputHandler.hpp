#pragma once

#include <SFML/Graphics.hpp>
#include <imgui.h>

#include "EventHandler.hpp"
#include "../Logger.hpp"
#include "../LogConsole.hpp"

class InputHandler : public EventHandler {
public:

	InputHandler();

	// override method to handle window events
	void handleEvents(sf::RenderWindow& window) override;

	// method to render the imgui console
	void renderConsole();

private:
	bool showConsole; // flag to toggle display
};