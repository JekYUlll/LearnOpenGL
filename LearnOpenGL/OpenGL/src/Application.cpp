#include "Application.h"

Application::Application(int width, int height, const char* title)
{
    this->window = init::Init("JekYUlll", width, height, 3, 3, true);
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::Run()
{
    while (!glfwWindowShouldClose(window)) {
        timer::SyncTime();

        Update(timer::deltaTime);
        Render();
    }
}

void Application::Update(float deltaTime)
{
    entityManager.UpdateAllEntities(deltaTime);
    // 如果有其他不属于 EntityManager 范畴的更新逻辑，也可以放在这里
}

void Application::Render()
{

}
