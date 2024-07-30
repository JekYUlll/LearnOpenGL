#include "Timer.h"

namespace timer
{
	float lastFrame = 0.0f;
	float currentFrame;
	float deltaTime;

	void SyncTime()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
}
