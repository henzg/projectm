#include "../include/Logger.hpp"

std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::init(const std::string& logFileName) {
	// console sink with color output
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_pattern("[%H:%M:%S] [%^1%$] %v");

	// file sink for loggin to a file
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFileName, true);
	fileSink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");

	// combine both sinks into one logger
	logger = std::make_shared<spdlog::logger>("GameLogger", spdlog::sinks_init_list{consoleSink, fileSink});
	spdlog::register_logger(logger);

	// set log level to debug (all logs will be shown)
	logger->set_level(spdlog::level::debug);
	logger->flush_on(spdlog::level::debug);

	spdlog::set_default_logger(logger);
}

void Logger::info(const std::string& message) {
	logger->info(message);
	LogConsole::getInstance().addLog("[INFO] " + message);
}

void Logger::debug(const std::string& message) {
	logger->debug(message);
	LogConsole::getInstance().addLog("[DEBUG] " + message);
}

void Logger::warn(const std::string& message) {
	logger->warn(message);
	LogConsole::getInstance().addLog("[WARN] " + message);
}

void Logger::error(const std::string& message) {
	logger->error(message);
	LogConsole::getInstance().addLog("[ERROR] " + message);
}