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
    // ���ð汾
    static void SetOpenGLVersion(const unsigned int& versionNum_1, const unsigned int& versionNum_2, const bool& isCore);
    // ��ӡ��ʼ��Ϣ
    static void PrintInitInfo(const unsigned int& width, const unsigned int& height);
    // ���ô���ͼ��
    static void SetWindowIcon(GLFWwindow* window, const std::string& iconPath);
    /// <summary>
    /// ��ʼ��GLEW��GLFW��ImGui����������
    /// </summary>
    /// <param name="windowName">���ڱ���</param>
    /// <param name="width">���ڿ��</param>
    /// <param name="height">���ڸ߶�</param>
    /// <param name="versionNum_1">���汾��</param>
    /// <param name="versionNum_2">�ΰ汾��</param>
    /// <param name="isCore">�Ƿ�ΪOpenGL core</param>
    /// <returns>����ָ��</returns>
    GLFWwindow* Init(const std::string& windowName, const unsigned int& width, const unsigned int& height, const unsigned int& versionNum_1, const unsigned int& versionNum_2, const bool& isCore);
}


#endif // !INIT_HPP
