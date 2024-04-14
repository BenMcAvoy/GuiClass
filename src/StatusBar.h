#pragma once

#include "globals.h"
#include "utils.h"
#include <imgui.h>

class StatusBar {
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
		}

		ImGui::EndMenu();
	}

	float windowWidth = ImGui::GetIO().DisplaySize.x;
	ImVec2 textSize = ImGui::CalcTextSize("No process selected");
	ImGui::SetCursorPosX((windowWidth - textSize.x) / 2);

	if (ImGui::Selectable("No process selected", false, ImGuiSelectableFlags_None, textSize)) {
		INFO("Picking a process\n");
	}


	ImGui::EndMainMenuBar();
}
