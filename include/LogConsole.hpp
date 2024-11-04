#pragma once

#include <imgui.h>
#include <vector>
#include <string>

class LogConsole {
public:
	LogConsole();

	// add log message
	void addLog(const std::string& message);

	void renderConsole(bool* p_open);

	void clear();

	// static instance f
	static LogConsole& getInstance();


private:
	ImGuiTextBuffer buffer;
	ImVector<int> lineOffsets;
	bool scrollToBottom;

};