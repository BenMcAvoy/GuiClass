#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "globals.cpp"
#include "logging.h"
#include "utils.h"

#include <imgui.h>

#include <string>
#include <vector>
#include <cctype>

class StatusBar {
	public:
		void Render() {
			ImGui::PushID("statusbar");

			ImGui::BeginMainMenuBar();

			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New", "Ctrl+N")) {}
				if (ImGui::MenuItem("Open", "Ctrl+O")) {}
				if (ImGui::MenuItem("Save", "Ctrl+S")) {}
				if (ImGui::MenuItem("Quit", "Ctrl+Q"))
					globals::shouldExit = true;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Process")) {
				bool disabled = globals::process.name == globals::emptyProcess.name;

				if (disabled)
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

				if (ImGui::MenuItem("Detach", "Ctrl+D", false, !disabled)) {
					GC_INFO("Detaching from process with handle %p\n", globals::process.handle);
					globals::process = globals::emptyProcess;

#ifdef _WIN32
					CloseHandle(globals::process.handle);
#endif
				}

				if (disabled)
					ImGui::PopStyleVar();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Debug")) {
				if (ImGui::MenuItem("Print handle")) {
					GC_INFO("Handle: %p\n", globals::process.handle);
				}

				if (ImGui::MenuItem("Print all logs")) {
					GC_INFO("Log output\n");
					GC_WARN("Log output\n");
					GC_ERROR("Log output\n");
				}

				ImGui::EndMenu();
			}

			std::string displayProcess = globals::process.name;
			if (globals::process.name != globals::emptyProcess.name)
				displayProcess += " : " + std::to_string(globals::process.pid);

			float windowWidth = ImGui::GetIO().DisplaySize.x;
			ImVec2 textSize = ImGui::CalcTextSize(displayProcess.c_str());
			ImGui::SetCursorPosX((windowWidth - textSize.x) / 2);

			if (ImGui::Selectable(displayProcess.c_str(), false, ImGuiSelectableFlags_None, textSize))
				ImGui::OpenPopup("Pick a process");

			if (ImGui::BeginPopupModal("Pick a process", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
					ImGui::CloseCurrentPopup();

				if (ImGui::BeginChild("Process list", ImVec2(480, 640), true)) {
					static char search[128] = "";
					ImGui::InputText("Search", search, IM_ARRAYSIZE(search));

					for (const Process &process : globals::processList) {
						std::string processLower = STR_LOWER(process.name);
						std::string searchLower = STR_LOWER(search);

						if (strstr(processLower.c_str(), searchLower.c_str()) == nullptr)
							continue;

						if (ImGui::Selectable(process.name.c_str(), false)) {
							globals::process = process;
							GC_INFO("Selected process %s with PID %d and handle %p\n", globals::process.name.c_str(), globals::process.pid, globals::process.handle);
							ImGui::CloseCurrentPopup();
						}
					}

					ImGui::Text("Processes shown: %lu", globals::processList.size());
				}

				ImGui::EndChild();
				ImGui::EndPopup();
			}


			ImGui::EndMainMenuBar();

			ImGui::PopID();
		}
};

#endif // STATUSBAR_H
