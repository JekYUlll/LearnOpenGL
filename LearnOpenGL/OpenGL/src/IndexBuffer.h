#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include "Debug.h"

class IndexBuffer
{
private:
	unsigned int _rendererID;
	unsigned int _count; // 有多少索引
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	// 获取索引个数
	inline unsigned int GetCount() const { return _count; }
};

#endif // !INDEXBUFFER_H