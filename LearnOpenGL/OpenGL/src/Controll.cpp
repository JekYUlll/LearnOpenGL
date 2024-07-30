#include "Controll.h"
	
namespace ctrl
{
	bool enableMouse = false;
	bool isWireframe = false;
	static bool canShowCursor = true; // 是否显示光标
	static bool keys[1024] = { false }; // 记录按键是否按下
	static float lastX = (float)(1920 / 2), lastY = (float)(1080 / 2); // 鼠标初始位置
	static bool firstMouse = true; // 是否是第一次按下鼠标

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) // from LearnOpenGL 教程中函数名是key_callback
	{
		if (action == GLFW_PRESS) {
			keys[key] = true;
			if (key == GLFW_KEY_ESCAPE) {
				// 按下ESC键,设置window窗口的WindowShouldClose属性为true
				std::cout << "[ESC pressed] window closed" << std::endl;
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
			if (key == GLFW_KEY_F11) {
				if (canShowCursor) {
					canShowCursor = false;
					GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
					std::cout << "[F11 pressed] hide cursor" << std::endl;
				}
				else {
					canShowCursor = true;
					GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
					std::cout << "[F11 pressed] show cursor" << std::endl;
				}
			}
			if (key == GLFW_KEY_F1) {
				if (!enableMouse) {
					enableMouse = true;
					std::cout << "[F1 pressed] enable mouse" << std::endl;
				}
				else {
					enableMouse = false;
					std::cout << "[F1 pressed] disable mouse" << std::endl;
				}
			}
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (enableMouse) {
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = (xpos - lastX) * sensitivity;
			float yoffset = (lastY - ypos) * sensitivity; // 相反的，因为y坐标的范围是从下往上的
			lastX = xpos;
			lastY = ypos;

			yaw += xoffset;
			pitch += yoffset;
			pitch = glm::clamp(pitch, -89.0f, 89.0f);

			glm::vec3 front{};
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(front);
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		fov_y -= yoffset * 0.20f;
		fov_y = glm::clamp(fov_y, 1.0f, 45.0f);
		// 会无限放大，原因未知
	}

	void MoveCamera()
	{
		// 移动相机前后
		if (keys[GLFW_KEY_W])
			cameraPos += cameraMove * cameraFront;
		if (keys[GLFW_KEY_S])
			cameraPos -= cameraMove * cameraFront;
		// 移动相机左右
		if (keys[GLFW_KEY_A])
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraMove;
		if (keys[GLFW_KEY_D])
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraMove;
		// 上升和下降
		if (keys[GLFW_KEY_SPACE])
			cameraPos += cameraMove * cameraUp;
		if (keys[GLFW_KEY_C])
			cameraPos -= cameraMove * cameraUp;
		if (keys[GLFW_KEY_LEFT_SHIFT]) 
			cameraSpeed = cameraSpeed_rush;
		else
			cameraSpeed = cameraSpeed_std;
	}
	// 切换为线框/填充模式
	void SetFrameMode()
	{
		if (isWireframe) {
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));  // 切换到线框模式
			std::cout << "[LINE mode]" << std::endl;
		}
		else {
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));  // 切换到填充模式
			std::cout << "[FILL mode]" << std::endl;
		}
	}
}