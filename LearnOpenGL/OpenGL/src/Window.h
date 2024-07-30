#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_EXPOSE_NATIVE_WIN32

#include <iostream>
// #include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

// 回调，尝试在改变窗口分辨率的时候保持图片长宽比不变
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 图片尽可能填充窗口
void AdaptToWindow(int& width, int& height, int winW, int WinH);
// 把窗口边框设置为黑色。没生效
// void SetWindowBorderColor(GLFWwindow* window, COLORREF color);

#endif // !WINDOW_H

