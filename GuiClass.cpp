#pragma comment(lib, "openGL32.lib")

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <stdio.h>

#define SETCOLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

#define INFO(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(10); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

#define WARN(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(14); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

#define ERROR(...) { \
	SYSTEMTIME st; \
	GetLocalTime(&st); \
	SETCOLOR(12); printf("[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds); SETCOLOR(7); \
	printf(__VA_ARGS__); \
}

void render() {
	// -------------- //
	// ---- MENU ---- //
	// -------------- //

	// Create the main menu bar
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("New", "Ctrl+N")) {}
		if (ImGui::MenuItem("Open", "Ctrl+O")) {}
		if (ImGui::MenuItem("Save", "Ctrl+S")) {}
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

	// -------------- //
	// --- RIBBON --- //
	// -------------- //

	// Create a window at the top of the screen for the ribbon
	ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 50), ImGuiCond_Always);
	ImGui::Begin("Ribbon", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImGui::Text("Ribbon");

	ImGui::End();
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
	io.Fonts->AddFontFromFileTTF("../../resources/JetBrainsMonoNerdFont-Regular.ttf", 20.0f);

	if (io.Fonts->Fonts.empty())
		ERROR("Failed to load font\n");

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	while (!glfwWindowShouldClose(window)) {
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

/*#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "opengl32.lib")

#include <windows.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"

#include "GLFW/glfw3.h"

#include <windows.h>
int main(void) {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1280, 720, "Hello, ImGui!", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello, ImGui!");
		ImGui::Text("Hello, world!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplGlfw_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}*/
