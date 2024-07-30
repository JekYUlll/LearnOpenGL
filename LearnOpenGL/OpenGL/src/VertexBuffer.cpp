#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    // 使用glGenBuffers函数和一个缓冲ID生成一个 顶点缓冲对象(Vertex Buffer Objects, VBO)
    GLCall(glGenBuffers(1, &_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
    // 把之前定义的顶点数据复制到缓冲的内存中
    // 第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
        // GL_STATIC_DRAW ：数据不会或几乎不会改变。
        // GL_DYNAMIC_DRAW：数据会被改变很多。
        // GL_STREAM_DRAW ：数据每次绘制时都会改变。
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &_rendererID));
}

// 绑定 vertex buffer
void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
}

// 解绑 vertex buffer
void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
