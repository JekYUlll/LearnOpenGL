#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Debug.h"
#include "Renderer.h"

extern const unsigned int WIDTH, HEIGHT;

// 自定义的枚举类，用于简要判断texture类型。进一步判断使用Assimp库的aiTextureType
static enum class TextureType
{
	IMAGE = 0, // 普通的纹理
	FRAME_BUFFER = 1, // 用作帧缓冲的纹理
	CUBE_MAP = 2 // 用作立方体贴图
};

class Texture
{
public:
	unsigned int _id;
private:
	std::string _filePath; // 纹理的路径
	unsigned char* _localBuffer; // 纹理的本地存储
	int _width, _height;
	int _BPP; // bits per pixel

public:
	aiString path;
	aiTextureType type;

public:
	// 读取本地路径的正常纹理
	Texture(const std::string& filePath, TextureType type = TextureType::IMAGE);
	// 帧缓冲纹理 弃用，设计失误
	Texture(unsigned int& id);
	Texture(unsigned int width, unsigned int height, GLenum format);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return this->_width; }
	inline int GetHeight() const { return this->_height; }
	inline unsigned int GetID() const { return this->_id; }

	void LoadCubemap(const std::vector<std::string>& faces);
	void LoadCubemap(const std::string& folderPath);
};




















#endif // !TEXTURE_H

