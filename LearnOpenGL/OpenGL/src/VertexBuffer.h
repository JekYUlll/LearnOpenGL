#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Debug.h"

class VertexBuffer
{
private:
	unsigned int _rendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};

#endif // !VERTEXBUFFER_H