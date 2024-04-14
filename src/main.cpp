#pragma comment(lib, "openGL32.lib")

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <stdio.h>

#include "StatusBar.h"
#include "globals.h"
#include "Ribbon.h"
#include "utils.h"

StatusBar statusBar;
Ribbon ribbon;

static void render() {
	// --- MENU --- //
	statusBar.Render();

	// -- RIBBON -- //
	ribbon.Render();
}

void update() {
	render();
}

int main(void) {
	if (!glfwInit())
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "GuiClass", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Set font to arial
	io.Fonts->AddFontFromFileTTF("JetBrainsMonoNerdFont-Regular.ttf", 20.0f);

	if (io.Fonts->Fonts.empty())
		ERROR("Failed to load font\n");

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	while (!glfwWindowShouldClose(window) && !globals::shouldExit) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		update();

		ImGui::Render();

		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
