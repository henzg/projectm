#include "../include/ConfigManager.hpp"
#include <fstream>
#include <iostream>
#include "../include/Logger.hpp"

const nlohmann::json& ConfigManager::loadConfig(const std::string& filename) {
	// cehc if config is loaded in cache
	auto it = configCache.find(filename);
	if (it != configCache.end()) {
		return it->second;
	}

	// full path to config file
	std::string fullPath = getConfigFilePath(filename);

	// debug log
	Logger::debug("Attempting to load config file at: " + fullPath);

	// attempt to load and parse the json file
	std::ifstream file(fullPath);
	if (!file.is_open()) {
		Logger::error("Could not open config file:" + fullPath);
		throw std::runtime_error("Config file could not be opened");
	}

	nlohmann::json jsonData;
	try {
		file >> jsonData;
	}
	catch (const nlohmann::json::parse_error& e) {
		Logger::error("Error parsing JSON in file: " + fullPath + ": " + e.what());
		throw;
	}


	// cache loaded json and return a reference to it
	configCache[filename] = jsonData;
	return configCache[filename];
}

bool ConfigManager::isConfigLoaded(const std::string& filename) const {
	return configCache.find(filename) != configCache.end();
}

void ConfigManager::clearConfig(const std::string& filename) {
	configCache.erase(filename);
}

void ConfigManager::clearAllConfigs() {
	configCache.clear();
}

std::string ConfigManager::getConfigFilePath(const std::string& filename) const {
	return "../../../configs/" + filename;
}




