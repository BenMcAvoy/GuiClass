#pragma once

#include "globals.cpp"
#include "element.h"
#include "logging.h"
#include "utils.h"

#include <imgui.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

class StatusBar : public Element {
	private:
		bool processPickerModalOpen = false;

	public:
		void Render() override {
			ImGui::BeginMainMenuBar();
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New", "Ctrl+N")) {}
				if (ImGui::MenuItem("Open", "Ctrl+O")) {}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {}
				if (ImGui::MenuItem("Quit", "Ctrl+Q")) {
					globals::shouldExit = true;
					INFO("Exiting %d\n", globals::shouldExit);
				}

				if (ImGui::BeginMenu("Debug")) {
					if (ImGui::MenuItem("Print handle address")) {
						INFO("Handle address: %p\n", &globals::process.handle);
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Process")) {
				bool disabled = globals::process.name == globals::emptyProcess.name;

				if (disabled)
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

				if (ImGui::MenuItem("Detach", "Ctrl+D", false, !disabled)) {
					INFO("Detaching from process with handle %p\n", &globals::process.handle);
					globals::process = globals::emptyProcess;

#ifdef _WIN32
					CloseHandle(globals::process.handle);
#endif
				}

				if (disabled)
					ImGui::PopStyleVar();

				ImGui::EndMenu();
			}

			float windowWidth = ImGui::GetIO().DisplaySize.x;
			ImVec2 textSize = ImGui::CalcTextSize(globals::process.name.c_str());
			ImGui::SetCursorPosX((windowWidth - textSize.x) / 2);

			const std::string displayProcess = globals::process.name + " : " + std::to_string(globals::process.pid);
			const std::string conditionalProcess = globals::process.name == globals::emptyProcess.name ? "Select a process" : displayProcess;
			if (ImGui::Selectable(conditionalProcess.c_str(), false, ImGuiSelectableFlags_None, textSize)) {
				ImGui::OpenPopup("Pick a process");
			}

			if (ImGui::BeginPopupModal("Pick a process", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::BeginChild("Process list", ImVec2(480, 640), true)) {
					static char search[128] = "";
					ImGui::InputText("Search", search, IM_ARRAYSIZE(search));
					ImGui::SameLine();
					ImGui::Text("Results: %lu", globals::processList.size());

					for (const Process &process : globals::processList) {
						std::string processLower = process.name;
						std::string searchLower = search;

						std::transform(processLower.begin(), processLower.end(), processLower.begin(), ::tolower);
						std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

						if (strstr(processLower.c_str(), searchLower.c_str()) == nullptr)
							continue;

						if (ImGui::Selectable(process.name.c_str(), false)) {
							globals::process = process;
							//this->selectedProcess = globals::process.name + " : " + std::to_string(globals::process.pid);

							INFO("Selected process %s with PID %d and handle %p\n", globals::process.name.c_str(), globals::process.pid, &globals::process.handle);

							ImGui::CloseCurrentPopup();
						}
					}
				}

				ImGui::EndChild();
				ImGui::EndPopup();
			}


			ImGui::EndMainMenuBar();
		}
};
