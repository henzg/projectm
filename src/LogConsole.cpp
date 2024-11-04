#include "LogConsole.hpp"
#include "Logger.hpp"
#include <iostream>

LogConsole::LogConsole() : scrollToBottom(false) {
	clear();
}

void LogConsole::addLog(const std::string& message) {
	std::cout << "adding log to imgui buffer" << message << std::endl;
	int oldSize = buffer.size();
	buffer.appendf("%s\n", message.c_str());
	for (int newSize = buffer.size(); oldSize < newSize; oldSize++)
		if (buffer[oldSize] == '\n')
			lineOffsets.push_back(oldSize + 1);
	
	scrollToBottom = true;
}

void LogConsole::renderConsole(bool* p_open) {
	if (!*p_open) {
		Logger::info("No *p_open");
		return;
	}
	
	ImGui::Begin("Console Log", p_open);

	// clear
	if (ImGui::Button("clear")) clear();
	ImGui::SameLine();
	bool copyToClipboard = ImGui::Button("Copy");

	ImGui::Separator();
	ImGui::BeginChild("scrolling_region", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (copyToClipboard)
		ImGui::LogToClipboard();

	if (!buffer.empty())
		ImGui::TextUnformatted(buffer.begin());
	else
		ImGui::Text("No logs available");

	if (scrollToBottom)
		ImGui::SetScrollHereY(1.0f);
	scrollToBottom = false;

	ImGui::EndChild();
	ImGui::End();
}

void LogConsole::clear() {
	buffer.clear();
	lineOffsets.clear();
	lineOffsets.push_back(0);
}

LogConsole& LogConsole::getInstance() {
	static LogConsole instance;
	return instance;
}