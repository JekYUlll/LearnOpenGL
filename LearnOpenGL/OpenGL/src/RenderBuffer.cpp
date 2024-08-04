#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height, GLenum internalFormat)
    : _id(0), _internalFormat(internalFormat)
{
    glGenRenderbuffers(1, &_id);
    glBindRenderbuffer(GL_RENDERBUFFER, _id);
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RenderBuffer::~RenderBuffer() {
    glDeleteRenderbuffers(1, &_id);
}

void RenderBuffer::Bind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, _id);
}

void RenderBuffer::Unbind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
