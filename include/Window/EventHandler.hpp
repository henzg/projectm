#pragma once

#include <SFML/Graphics.hpp>

class EventHandler {
public:
	virtual void handleEvents(sf::RenderWindow& window) = 0;
};