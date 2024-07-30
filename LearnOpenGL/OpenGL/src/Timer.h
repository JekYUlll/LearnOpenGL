#ifndef TIMER_H
#define TIMER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 计时
namespace timer
{
	extern float lastFrame;   // 上一帧的时间
	extern float currentFrame;
	extern float deltaTime;   // 当前帧遇上一帧的时间差

	void SyncTime(); // 同步时间
	

}








#endif // !TIMER_H



