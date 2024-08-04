#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "config.h"
#include "Gui.h"
#include "Debug.h"
#include "Init.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include "Component.h"
#include "EntityManager.h" 
#include "Timer.h"

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();
    void Run();

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        T* component(new T(std::forward<TArgs>(args)...));
        std::unique_ptr<Component> uPtr(component);
        components.emplace_back(std::move(uPtr));
        return *component;
    }

private:
    void Update(float deltaTime); // Update 方法负责调用 Application 所有组件的 Update 方法
    void Render();

    GLFWwindow* window;
    std::vector<std::unique_ptr<Component>> components;
    EntityManager entityManager;
};
