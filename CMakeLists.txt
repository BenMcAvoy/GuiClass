cmake_minimum_required(VERSION 3.0)
project(CMakeDemo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(imgui STATIC
    libs/imgui/imgui.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_widgets.cpp
)

add_subdirectory(libs/glfw)

add_executable(main main.cpp)

target_link_libraries(main glfw imgui)
include_directories(${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)
