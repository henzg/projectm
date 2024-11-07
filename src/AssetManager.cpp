#include "../include/AssetManager.hpp"
#include "../include/Logger.hpp"

#include <stdexcept>
#include <iostream>

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

void AssetManager::loadAnimationFrames(const std::string& characterName, const std::string& state, const std::string path, int frames) {
	std::vector<sf::Texture> frameTextures;

	for (int i = 1; i <= frames; ++i) {
		sf::Texture texture;
		std::string filepath = path + "/" + state + std::to_string(i) + ".png";
		if (!texture.loadFromFile(filepath)) {
			Logger::error("Failed to load texture: " + filepath);
			throw std::runtime_error("Failed to load texture: " + filepath);
		}

		frameTextures.push_back(std::move(texture));
	}
	animations[characterName][state] = std::move(frameTextures);
}

const std::vector<sf::Texture>& AssetManager::getAnimationFrames(const std::string& characterName, const std::string& state) {
	auto charIt = animations.find(characterName);
	if (charIt == animations.end() || charIt->second.find(state) == charIt->second.end()) {
		Logger::error("ANimation not found for character: " + characterName + ", state: " + state);
	}
	return charIt->second[state];
}