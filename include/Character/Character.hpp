#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "../AssetManager.hpp"
#include "../ConfigManager.hpp"

class Item;
class Weapon;
class Ability;
class Gear;

class Character {
public:
	Character(const std::string& name, int health);
	virtual ~Character() = default;

	// Getters and setters
	const std::string& getName() const;
	int getHealth() const;
	void setHealth(int health);

	// inventory
	void addItemToInventory(std::shared_ptr<Item> item);
	void removeItemFromInventory(const std::string& itemName);
	const std::vector<std::shared_ptr<Item>>& getInventory() const;

	// combat
	void attack(Character& target);
	void useAbility(Character& target);

	// Equipment
	void equipWeapon(std::shared_ptr<Weapon> weapon);
	void equipGear(const std::string& gearSlot, std::shared_ptr<Gear> gear);

	// Sprite loading and anaimation
	void loadSprite(const std::string& configFilePath, AssetManager& assetManager, ConfigManager& configManager);
	void updateANimation(float deltaTime);

	// render
	void render(sf::RenderWindow& window);

protected:
	const std::string& name;
	int health;
	std::shared_ptr<Weapon> weapon;
	std::shared_ptr<Ability> ability;
	std::unordered_map<std::string, std::shared_ptr<Gear>> gearSlots;
	std::vector<std::shared_ptr<Item>> inventory;

	sf::Sprite sprite;
	std::vector<sf::Texture> animationFrames;
	float animationSpeed;
	float currentFrame;
};