#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Debug.h"
#include "Renderer.h"

extern enum aiTextureType;

class Texture
{
private:
	unsigned int _rendererID;
	std::string _filePath; // 纹理的路径
	unsigned char* _localBuffer; // 纹理的本地存储
	int _width, _height;
	int _BPP; // bits per pixel

public:
	aiString path;
	aiTextureType type;

public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return this->_width; }
	inline int GetHeight() const { return this->_height; }
	inline unsigned int GetID() const { return this->_rendererID; }
};




















#endif // !TEXTURE_H

