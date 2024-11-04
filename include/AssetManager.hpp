#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

/*
AssetManager uses unordered_maps for efficientcy and simplicity sake. Less overhead than using shared ptrs and easier memory allocation. Pulling specific textures is also easier with the way it works with indexes

*/


class AssetManager {
public:
	AssetManager() = default;
	~AssetManager() = default;

	// load texture and store it with a unique ID
	void loadTexture(const std::string& name, const std::string& filepath);

	// Retrieve a texture by name
	const sf::Texture& getTexture(const std::string& name);

private:
	std::unordered_map<std::string, sf::Texture> textures;
};