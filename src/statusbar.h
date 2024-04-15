#pragma once

#include "globals.cpp"
#include "element.h"
#include "logging.h"

#include <imgui.h>
#include <string>

class StatusBar : public Element {
	private:
		bool processPickerModalOpen = false;
		std::string selectedProcess = "Select a process";

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

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Process")) {
				bool disabled = globals::processHandle == nullptr;

				if (disabled)
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

				if (ImGui::MenuItem("Detach", "Ctrl+D", false, !disabled)) {
					INFO("Detaching from process\n");
					globals::processHandle = nullptr;

#ifdef _WIN32
					CloseHandle(globals::processHandle);
#endif
				}

				if (disabled)
					ImGui::PopStyleVar();

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
				if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape))) {
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::BeginChild("Process list", ImVec2(400, 300), true)) {
					static char search[128] = "";
					ImGui::InputText("Search", search, IM_ARRAYSIZE(search));
				}

				ImGui::EndChild();
				ImGui::EndPopup();
			}


			ImGui::EndMainMenuBar();
		}
};
