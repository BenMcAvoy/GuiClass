#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <stdio.h>

#include "font.h"
#include "logging.h"

#include "globals.cpp"

#include "ribbon.h"
#include "statusbar.h"

Ribbon ribbon;
StatusBar statusbar;

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "GuiClass", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Initialize ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF(fonts::JetBrainsMonoNerdFont_Regular_ttf, sizeof(fonts::JetBrainsMonoNerdFont_Regular_ttf), 20.0f, &config, io.Fonts->GetGlyphRangesDefault());

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

	if (io.Fonts->Fonts.empty())
		ERROR("Failed to load font\n");

	/* Setup Dear ImGui style */
	ImGui::StyleColorsDark();

	/* Setup Platform/Renderer bindings */
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	double lastProcessListUpdate = 0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && !globals::shouldExit) {
		/* Update */
		if (glfwGetTime() - lastProcessListUpdate >= 1.0) {
			globals::processList = GetProcessList();
			lastProcessListUpdate = glfwGetTime();
			//INFO("Updated process list of length %lu\n", globals::processList.size());
		}

		glfwPollEvents();

		/* Start the ImGui frame */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Render UI */
		ribbon.Render();
		statusbar.Render();

		ImGui::Render();

		/* Render OpenGL */
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	/* Cleanup */
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
