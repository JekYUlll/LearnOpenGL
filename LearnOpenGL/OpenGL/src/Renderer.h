#ifndef RENDERER_H
#define RENDERER_H

#include "Debug.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <imgui/imgui.h>

enum class RenderMode
{
	MODEL,
	CUBE
};

class Renderer
{
private:
	RenderMode _renderMode;
public:
	// 单例模式
	static Renderer& getInstance();

	void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawArrays(const VertexArray& va, const Shader& shader, GLenum mode, GLint first, GLsizei count) const;

	void Clear();
	// 设置背景颜色
	void SetBgColor(float r, float g, float b);
	// 设置背景颜色(带透明度)
	void SetBgColor(float r, float g, float b, float a);
	// 设置背景颜色(默认为黑)
	void SetBgColor();
	void SetBgColor(ImVec4 clear_color);

	inline RenderMode GetRenderMode() const { return this->_renderMode; }
	// 切换到立方体模式，会改变 Texture 类的一些实现
	inline void SwitchToCube() { this->_renderMode = RenderMode::CUBE; }
private:
	Renderer() : _renderMode(RenderMode::MODEL) {}  // 私有构造函数
	Renderer(const Renderer&) = delete; // 禁止拷贝构造
	Renderer& operator=(const Renderer&) = delete; // 禁止赋值
};

#endif // !RENDERER_H


