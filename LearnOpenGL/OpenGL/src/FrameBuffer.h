#pragma once

#include "Debug.h"
#include "Texture.h"
#include "Renderbuffer.h"
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern const unsigned int WIDTH, HEIGHT;

// Ö¡»º³å FBO
class FrameBuffer {
private:
    unsigned int _id;
    std::vector<std::shared_ptr<Texture>> _colorAttachments;
    std::shared_ptr<RenderBuffer> _renderBuffer;

public:
    FrameBuffer();
    ~FrameBuffer();

    void Bind() const;
    void Unbind() const;
    void AttachColorTexture(const std::shared_ptr<Texture>& texture, unsigned int attachmentIndex);
    void AttachDepthStencilBuffer(const std::shared_ptr<RenderBuffer>& renderBuffer);
    void AttachDepthStencilTexture(const std::shared_ptr<Texture>& texture);
    bool CheckStatus() const;

    unsigned int GetID() const { return _id; }
};
