#pragma once

#include "globals.h"
#include "utils.h"
#include <imgui.h>

class StatusBar {
private:
	bool processPickerModalOpen = false;
	std::string selectedProcess = "No process selected";

public:
	void Render();
};

void StatusBar::Render() {
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("New", "Ctrl+N")) {}
		if (ImGui::MenuItem("Open", "Ctrl+O")) {}
		if (ImGui::MenuItem("Save", "Ctrl+S")) {}
		if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
			globals::shouldExit = true;
			INFO("Exiting %d\n", globals::shouldExit);
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Process")) {
		if (ImGui::MenuItem("Pick a process")) {
			INFO("Picking a process\n");
			ImGui::OpenPopup("Pick a process");
		}

		ImGui::EndMenu();
	}

	float windowWidth = ImGui::GetIO().DisplaySize.x;
	ImVec2 textSize = ImGui::CalcTextSize(this->selectedProcess.c_str());
	ImGui::SetCursorPosX((windowWidth - textSize.x) / 2);

	if (ImGui::Selectable(this->selectedProcess.c_str(), false, ImGuiSelectableFlags_None, textSize)) {
		INFO("Picking a process\n");
		ImGui::OpenPopup("Pick a process");
	}

	if (ImGui::BeginPopupModal("Pick a process", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		if (ImGui::BeginChild("Process list", ImVec2(400, 300), true)) {
			// Search
			static char search[128] = "";
			ImGui::InputText("Search", search, IM_ARRAYSIZE(search));

			// Get process list
			std::vector<std::string> processes = GetProcessList();

			// Filter processes based on search (case insensitive)
			std::vector<std::string> filteredProcesses;
			for (auto& process : processes) {
				if (strstr(toLower((char*)process.c_str()), toLower(search)) || strlen(search) == 0) {
					filteredProcesses.push_back(process);
				}
			}

			for (auto& process : filteredProcesses) {
				if (ImGui::Selectable(process.c_str())) {
					INFO("Selected process: %s\n", process.c_str());
					selectedProcess = process;

					globals::processHandle = GetProcessHandle(process);
					INFO("Process handle: %p\n", &globals::processHandle);

					ImGui::CloseCurrentPopup();
				}
			}
		}

		ImGui::EndChild();
		ImGui::EndPopup();
	}


	ImGui::EndMainMenuBar();
}
