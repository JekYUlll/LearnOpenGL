#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Debug.h"
#include "Renderer.h"

extern const unsigned int WIDTH, HEIGHT;

// �Զ����ö���࣬���ڼ�Ҫ�ж�texture���͡���һ���ж�ʹ��Assimp���aiTextureType
static enum class TextureType
{
	IMAGE = 0, // ��ͨ������
	FRAME_BUFFER = 1, // ����֡���������
	CUBE_MAP = 2 // ������������ͼ
};

class Texture
{
public:
	unsigned int _id;
private:
	std::string _filePath; // �����·��
	unsigned char* _localBuffer; // ����ı��ش洢
	int _width, _height;
	int _BPP; // bits per pixel

public:
	aiString path;
	aiTextureType type;

public:
	// ��ȡ����·������������
	Texture(const std::string& filePath, TextureType type = TextureType::IMAGE);
	// ֡�������� ���ã����ʧ��
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

