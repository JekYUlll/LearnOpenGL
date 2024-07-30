#include "Application.h"

Application::Application(int width, int height, const char* title)
{
    if (!glfwInit()) {
        // Initialization failed
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::Run()
{
}

void Application::Update(float deltaTime)
{
}

void Application::Render()
{
}
