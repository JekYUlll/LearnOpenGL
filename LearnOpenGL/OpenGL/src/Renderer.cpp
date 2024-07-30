#include "Renderer.h"

Renderer& Renderer::getInstance()
{
	static Renderer instance;
	return instance;
}

void Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Use();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawArrays(const VertexArray& va, const Shader& shader, GLenum mode, GLint first, GLsizei count) const
{
	shader.Use();
	va.Bind();
	GLCall(glDrawArrays(mode, first, count));
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void Renderer::SetBgColor(float r, float g, float b, float a = 1.0f)
{
	GLCall(glClearColor(r, g, b, a));
}

void Renderer::SetBgColor(float r, float g, float b)
{
	GLCall(glClearColor(r, g, b, 1.0f));
}

void Renderer::SetBgColor()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

void Renderer::SetBgColor(ImVec4 clear_color)
{
	GLCall(glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w));
}
