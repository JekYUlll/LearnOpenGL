#pragma once
#include "Debug.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern const unsigned int WIDTH, HEIGHT;

class RenderBuffer {
private:
    unsigned int _id;
    GLenum _internalFormat;
public:
    RenderBuffer(unsigned int width, unsigned int height, GLenum internalFormat);
    ~RenderBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetID() const { return _id; }
};