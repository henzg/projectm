#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>


class ConfigManager {
public:
	// loads json config file and caches it
	const nlohmann::json& loadConfig(const std::string& filename);

	// check if config is loaded
	bool isConfigLoaded(const std::string& filename) const;

	// clear specific config from cache
	void clearConfig(const std::string& filename);

	// clear all cached configs
	void clearAllConfigs();

private:
	std::unordered_map<std::string, nlohmann::json> configCache;
	// helper function to get full path
	std::string getConfigFilePath(const std::string& filename) const;
};