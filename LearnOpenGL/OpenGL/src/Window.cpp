#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "Framebuffer size changed: " << width << "x" << height << std::endl;
    glViewport(0, 0, width, height);

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    Shader* shader = static_cast<Shader*>(glfwGetWindowUserPointer(window));
    shader->Use();
    shader->SetUniform("projection", projection);
}

void AdaptToWindow(int& width, int& height, int winW, int winH)
{
	double  wRatio = winW * 1.0f / width;
	double  hRatio = winH * 1.0f / height;
	if (wRatio < hRatio) {
		width = winW;
		height = (int)(wRatio * height);
	}
	else {
		height = winH;
		width = (int)(hRatio * width);
	}
}

//void SetWindowBorderColor(GLFWwindow* window, COLORREF color)
//{
//    HWND hwnd = glfwGetWin32Window(window);
//    if (hwnd)
//    {
//        BOOL enable = TRUE; // 设置窗口的属性
//        HRESULT hr = DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &color, sizeof(color));
//        if (FAILED(hr))
//        {
//            // 处理错误
//            std::cerr << "Failed to set window border color, HRESULT: " << hr << std::endl;
//        }
//    }
//}