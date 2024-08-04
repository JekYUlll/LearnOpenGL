#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "Debug.h"
#include <glm/glm.hpp>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(const unsigned int& type)
    {
        switch (type)
        {
        case GL_FLOAT:         return 4;
        case GL_UNSIGNED_INT:  return 4;
        case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

typedef std::vector<VertexBufferElement> Buffers;

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;

public:
    VertexBufferLayout()
        : _stride(0) {}

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(false, "Unsupported type");
    }

    template<>
    void Push<float>(unsigned int count)
    {
        _elements.push_back({ GL_FLOAT, count, GL_FALSE });
        _stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        _elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        _stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        _elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        _stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    template<>
    void Push<glm::vec2>(unsigned int count)
    {
        _elements.push_back({ GL_FLOAT, count * 2, GL_FALSE });
        _stride += count * 2 * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<glm::vec3>(unsigned int count)
    {
        _elements.push_back({ GL_FLOAT, count * 3, GL_FALSE });
        _stride += count * 3 * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<glm::vec4>(unsigned int count)
    {
        _elements.push_back({ GL_FLOAT, count * 4, GL_FALSE });
        _stride += count * 4 * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    inline const std::vector<VertexBufferElement>& GetElements() const { return _elements; }
    inline unsigned int GetStride() const { return _stride; }
};
#endif // !VERTEXBUFFERLAYOUT_H
