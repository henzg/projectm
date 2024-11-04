#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <string>

#include "LogConsole.hpp"


class Logger {
public:
	static void init(const std::string& logFileName = "game_log.txt");

	static void info(const std::string& message);
	static void debug(const std::string& message);
	static void warn(const std::string& message);
	static void error(const std::string& message);

private:
	static std::shared_ptr<spdlog::logger> logger;
};