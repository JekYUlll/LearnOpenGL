#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() : _id(0) {
    glGenFramebuffers(1, &_id);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &_id);
}

void FrameBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

void FrameBuffer::Unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::AttachColorTexture(const std::shared_ptr<Texture>& texture, unsigned int attachmentIndex) {
    Bind();
    _colorAttachments.push_back(texture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentIndex, GL_TEXTURE_2D, texture->GetID(), 0);
    Unbind();
}

void FrameBuffer::AttachDepthStencilBuffer(const std::shared_ptr<RenderBuffer>& renderBuffer) {
    Bind();
    _renderBuffer = renderBuffer;
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->GetID());
    Unbind();
}

void FrameBuffer::AttachDepthStencilTexture(const std::shared_ptr<Texture>& texture) {
    Bind();
    _renderBuffer.reset(); // 清除可能的渲染缓冲
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0);
    Unbind();
}

bool FrameBuffer::CheckStatus() const {
    Bind();
    bool isComplete = (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    Unbind();
    return isComplete;
}
