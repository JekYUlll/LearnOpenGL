#ifndef KEYCONTROLL_H
#define KEYCONTROLL_H
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Debug.h"
#include "Timer.h"

extern const unsigned int WIDTH;
extern const unsigned int HEIGHT;

// 控制系统
namespace ctrl
{
	extern bool isWireframe; // 是否为线框模式
	extern bool enableMouse; // 是否可以使用鼠标移动视角

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void MoveCamera();
	void SetFrameMode();
}

#endif // !KEYCONTROLL_H
