#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <stdio.h>

/* Called for rendering */
void render() {
	ImGui::Begin("ImGui");

	ImGui::Text("Hello, world!");

	ImGui::End();
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

		/* Initialize ImGui */
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		/* Setup Dear ImGui style */
		ImGui::StyleColorsDark();

		/* Setup Platform/Renderer bindings */
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			/* Start the ImGui frame */
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			/* Render ImGui */
			render();
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
