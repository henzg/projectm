#include "../include/Character/Item.hpp"

Item::Item(const std::string name) : name(name) {}

const std::string Item::getName() { return name; }