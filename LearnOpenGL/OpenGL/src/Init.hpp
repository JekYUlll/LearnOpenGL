#ifndef INIT_HPP
#define INIT_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"

#include "Console.h"
#include "Debug.h"
#include "Controll.h"
#include "config.h"
#include "Gui.h"
#include "Renderer.h"

namespace init {
    // 设置版本
    static void SetOpenGLVersion(const unsigned int& versionNum_1, const unsigned int& versionNum_2, const bool& isCore)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionNum_1); // 主版本
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionNum_2); // 次版本
        if (isCore)
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 配置设为核心配置文件(core)
        else
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // 兼容配置文件(compat)
    }
    // 打印初始信息
    static void PrintInitInfo(const unsigned int& width, const unsigned int& height) {
#ifdef _DEBUG
        std::cout << "[Debug mode]" << std::endl;
#else
        std::cout << "[Release 1.0]" << std::endl;
#endif
        if (Renderer::getInstance().GetRenderMode() == RenderMode::MODEL) {
            std::cout << "[Render Mode: MODEL]" << std::endl;
        }
        else if (Renderer::getInstance().GetRenderMode() == RenderMode::CUBE)
        {
            std::cout << "[Render Mode: CUBE]" << std::endl;
        }
        SET_CONSOLE_TEXT_COLOR(FOREGROUND_GREEN);
        std::cout << "  ___                    ____ _    \n"
                  << " / _ \\ _ __   ___ _ __  / ___| |   \n"
                  << "| | | | '_ \\ / _ \\ '_ \\| |  _| |   \n"
                  << "| |_| | |_) |  __/ | | | |_| | |   \n"
                  << " \\___/| .__/ \\___|_| |_|\\____|_|   \n"
                  << "      |_|                          \n" << std::endl; // pyfiglet
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "ImGui version: " << IMGUI_VERSION << std::endl;
        // 打印分辨率
        std::cout << "Resolution: " << width << " * " << height << std::endl;
        int nrAttributes = 0; // 顶点属性上限
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
        SET_CONSOLE_TEXT_COLOR(FOREGROUND_RED);
        std::cout << "  <======>\n"  << std::endl;
        SET_CONSOLE_TEXT_COLOR(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    // 设置窗口图标
    static void SetWindowIcon(GLFWwindow* window, const std::string& iconPath) {
        int width, height, channels;
        unsigned char* pixels = stbi_load(iconPath.c_str(), &width, &height, &channels, 4);
        if (pixels) {
            GLFWimage icon{};
            icon.width = width;
            icon.height = height;
            icon.pixels = pixels;
            glfwSetWindowIcon(window, 1, &icon);
            stbi_image_free(pixels);
        }
        else {
            std::cerr << "Failed to load icon image: " << iconPath << std::endl;
        }
    }
    /// <summary>
    /// 初始化GLEW，GLFW，ImGui，创建窗口
    /// </summary>
    /// <param name="windowName">窗口标题</param>
    /// <param name="width">窗口宽度</param>
    /// <param name="height">窗口高度</param>
    /// <param name="versionNum_1">主版本号</param>
    /// <param name="versionNum_2">次版本号</param>
    /// <param name="isCore">是否为OpenGL core</param>
    /// <returns>窗口指针</returns>
    GLFWwindow* Init(const std::string& windowName, const unsigned int& width, const unsigned int& height, const unsigned int& versionNum_1, const unsigned int& versionNum_2, const bool& isCore)
    {
        GLFWwindow* window;
        /* Initialize the library */
        if (!glfwInit()) {
            std::cout << "Failed to init GLFW!" << std::endl;
            return nullptr;
        }
        init::SetOpenGLVersion(versionNum_1, versionNum_2, isCore);
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
        if (!window) {
            glfwTerminate();
            std::cout << "Failed to create window!" << std::endl;
            return nullptr;
        }
        SetWindowIcon(window, "res/icon/opengl.png"); // 设置图标
        glfwMakeContextCurrent(window); /* Make the window's context current */
#ifdef VERTICAL_SYN
        GLCall(glfwSwapInterval(1)); // 设置垂直同步
#endif // VERTICAL_SYN
        GLCall(glfwSetKeyCallback(window, ctrl::key_callback)); // 设置按键回调
        GLCall(glfwSetCursorPosCallback(window, ctrl::mouse_callback)); // 设置鼠标回调
        GLCall(glfwSetScrollCallback(window, ctrl::scroll_callback)); // 注册滚动回调函数
        // GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED)); // 开局隐藏指针
        // 初始化 GLEW
        if (glewInit() != GLEW_OK) {
            std::cout << "GLEW init Error!" << std::endl;
            return nullptr;
        }
        PrintInitInfo(width, height);
        return window;
    }
}

#endif // !INIT_HPP
