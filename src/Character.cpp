#include "../include/Character/Character.hpp"
#include "../include/Character/Item.hpp"
#include "../include/Character/Weapon.hpp"
#include "../include/Character/Ability.hpp"
#include "../include/Character/Gear.hpp"
#include "../include/ConfigManager.hpp"
#include <iostream>

Character::Character(const std::string& name, int health) :
	name(name),
	health(health),
	weapon(nullptr),
	ability(nullptr),
	animationSpeed(0.1f),
	currentFrame(0.0f) {}

const std::string& Character::getName() const { return name; }

int Character::getHealth() const { return health; }
void Character::setHealth(int health) { this->health = health; }

void Character::addItemToInventory(std::shared_ptr<Item> item) {
	inventory.push_back(item);
}

void Character::removeItemFromInventory(const std::string& itemName) {
	inventory.erase(
		std::remove_if(inventory.begin(), inventory.end(),
			[&itemName](const std::shared_ptr<Item>& item) {
				return item->getName() == itemName;
			}),
		inventory.end());
}

const std::vector<std::shared_ptr<Item>>& Character::getInventory() const {
	return inventory;
}