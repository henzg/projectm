#include <../include/Window/Window.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

Window::Window(const std::string& title, int width, int height) {
	window.create(sf::VideoMode(width, height), title);
	window.setFramerateLimit(60);
}

Window::~Window() {
	// cleanup if needed
}

bool Window::isOpen() const {
	return window.isOpen();
}

void Window::beginDraw() {
	window.clear(sf::Color::Red);
}

void Window::endDraw() {
	window.display();
}

sf::RenderWindow& Window::getRenderWindow() {
	return window;
}

void Window::setEventHandler(EventHandler* handler) {
	this->eventHandler = handler;
}