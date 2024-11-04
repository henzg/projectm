#include "../include/AssetManager.hpp"


void AssetManager::loadTexture(const std::string& name, const std::string& filepath) {
	sf::Texture texture;
	if (!texture.loadFromFile(filepath)) {
		throw std::runtime_error("Failed to load texture: " + filepath);
	}
	textures[name] = std::move(texture);
}

const sf::Texture& AssetManager::getTexture(const std::string& name) {
	auto it = textures.find(name);
	if (it == textures.end()) {
		throw std::runtime_error("Texture not found: " + name);
	}
	return it->second;
}