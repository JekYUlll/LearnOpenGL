#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Debug.h"
#include "Controll.h"

class Gui final {
private:
    ImGuiIO* _io;
    float _fontScale;
    static bool _initialized;
public:
    static Gui& getInstance(); 

    void Init(GLFWwindow* window, bool install_callbacks, const char* glsl_version); 

    void SetFont(const std::string& fontPath, const float& scale);

    void SetFontGlobalScale(const float& scale); 

    void StartDraw();
    void Render(GLFWwindow* window);

    void CleanUp();

    ImGuiIO& GetIO(); 

private:
    Gui() : _io(nullptr), _fontScale(1.0f) { _initialized = false; }
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;
};

#endif // !GUI_H



