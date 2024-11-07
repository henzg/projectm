#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

class Renderer {
public:
    Renderer(sf::RenderWindow& window);
    void renderCharacterAnimation(AssetManager& assetManager, const std::string& character, const std::string& state, float frameDuration, float deltaTime);

private:
    sf::RenderWindow& window;
    int currentFrame = 0;
    float elapsedTime = 0.0f;
};