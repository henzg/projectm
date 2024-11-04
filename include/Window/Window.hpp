#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "EventHandler.hpp"


class Window {
public:
	Window(const std::string& title= "Game Window", int width = 800, int height = 600);
	~Window();

	// checks if window is open
	bool isOpen() const;

	// Method to clear, draw, and display
	void beginDraw();
	void endDraw();
	sf::RenderWindow& getRenderWindow();

	void setEventHandler(EventHandler* handler);

private:
	sf::RenderWindow window;
	EventHandler* eventHandler;

};