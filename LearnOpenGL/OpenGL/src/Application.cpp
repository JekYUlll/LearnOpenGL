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
    // ��������������� EntityManager ����ĸ����߼���Ҳ���Է�������
}

void Application::Render()
{

}
