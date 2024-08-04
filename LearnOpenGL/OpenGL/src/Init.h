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
    static void SetOpenGLVersion(const unsigned int& versionNum_1, const unsigned int& versionNum_2, const bool& isCore);
    // 打印初始信息
    static void PrintInitInfo(const unsigned int& width, const unsigned int& height);
    // 设置窗口图标
    static void SetWindowIcon(GLFWwindow* window, const std::string& iconPath);
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
    GLFWwindow* Init(const std::string& windowName, const unsigned int& width, const unsigned int& height, const unsigned int& versionNum_1, const unsigned int& versionNum_2, const bool& isCore);
}


#endif // !INIT_HPP
