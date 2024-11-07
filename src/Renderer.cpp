#include "Renderer.hpp"

Renderer::Renderer(sf::RenderWindow& window) : window(window) {}

void Renderer::renderCharacterAnimation(AssetManager& assetManager, const std::string& character, const std::string& state, float frameDuration, float deltaTime) {
    const auto& frames = assetManager.getAnimationFrames(character, state);

    // Accumulate delta time
    elapsedTime += deltaTime;

    // Advance frame when elapsed time exceeds the frame duration
    if (elapsedTime >= frameDuration) {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % frames.size();  // Cycle through frames
    }

    // Draw the current frame
    sf::Sprite sprite(frames[currentFrame]);
    window.draw(sprite);
}