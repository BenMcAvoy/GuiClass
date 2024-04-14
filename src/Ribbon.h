#pragma once

#include "utils.h"
#include <imgui.h>

class Ribbon {
public:
	void Render();
};

void Ribbon::Render() {
	ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 96), ImGuiCond_Always);
	ImGui::Begin("Ribbon", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImGui::Text("Ribbon");

	ImGui::End();
}
