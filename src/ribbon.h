#pragma once

#include "element.h"
#include "logging.h"
#include <imgui.h>

// TODO: Modify this to implement a widget properly for Ribbon
// Context: https://github.com/ocornut/imgui/issues/2992
class Ribbon : public Element {
	public:
		void Render() override {
			ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 96), ImGuiCond_Always);
			ImGui::Begin("Ribbon", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

			ImGui::Columns(3, "ribbon", false);
			ImGui::SetColumnWidth(0, 96);
			ImGui::SetColumnWidth(1, 96);

			const ImVec2 size = ImVec2(96, 24);

			if (ImGui::Button("Add 4", size)) {
				INFO("Add 4 callback\n");
			};

			if (ImGui::Button("Add 16", size)) {
				INFO("Add 16 callback\n");
			};

			if (ImGui::Button("Add 256", size)) {
				INFO("Add 256 callback\n");
			};

			ImGui::NextColumn();

			if (ImGui::Button("Sub 4", size)) {
				INFO("Subtract 4 callback\n");
			};

			if (ImGui::Button("Sub 16", size)) {
				INFO("Subtract 16 callback\n");
			};

			if (ImGui::Button("Sub 256", size)) {
				INFO("Subtract 256 callback\n");
			};

			ImGui::End();
		}
};
