#include "Texture.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

static void FlipImageVertically(unsigned char* data, int width, int height, int channels)
{
	int stride = width * channels;
	unsigned char* row = new unsigned char[stride];
	for (int y = 0; y < height / 2; y++)
	{
		unsigned char* row1 = data + y * stride;
		unsigned char* row2 = data + (height - y - 1) * stride;
		memcpy(row, row1, stride);
		memcpy(row1, row2, stride);
		memcpy(row2, row, stride);
	}
	delete[] row;
}

Texture::Texture(const std::string& filePath, TextureType type)
	: _id(0), _filePath(filePath), _localBuffer(nullptr), _width(0), _height(0), _BPP(0), type(aiTextureType::aiTextureType_NONE)
{
	std::ifstream file(filePath);
	if (!file.good()) {
		std::cerr << "Texture file does not exist: " << filePath << std::endl;
		return;
	}
	file.close();

	stbi_set_flip_vertically_on_load(1); // OpenGL (0,0) 在左下角，所以需要翻转

	_localBuffer = stbi_load(_filePath.c_str(), &_width, &_height, &_BPP, 0); // 当 req_comp 设置为 0 时，表示 STB Image 库应该自动决定通道数
	
	if (_localBuffer) {
		std::cout << "Succeed to load texture: \"" << _filePath << "\". " << "" << _width << " * " << _height << ", BPP: " << _BPP << std::endl;

		GLenum format = GL_RGB;
		if (_BPP == 1)
			format = GL_RED;
		else if (_BPP == 3)
			format = GL_RGB;
		else if (_BPP == 4)
			format = GL_RGBA;

		GLCall(glGenTextures(1, &_id));
		GLCall(glBindTexture(GL_TEXTURE_2D, _id));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, _localBuffer)); // Cherno教程里这句在比较后面的位置  GL_RGBA8 表示内部格式为 8 位的 RGBA（红、绿、蓝、透明通道）格式。这意味着每个颜色通道都有 8 位（1 个字节）的存储空间，共计 32 位（4 个字节）存储一个像素。使用这种格式时，每个像素都有一个红色、一个绿色、一个蓝色和一个透明通道，适用于需要透明度信息的纹理，例如带有透明背景的图像。
		
		if (Renderer::getInstance().GetRenderMode() == RenderMode::MODEL) {
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		}
		else if (Renderer::getInstance().GetRenderMode() == RenderMode::CUBE) {
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		}
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
	else {
		std::cerr << "Failed to load texture: " << _filePath << std::endl;
	}
	if (_localBuffer) {
#ifdef _DEBUG
		//int pixelSize = _BPP; // 每个像素的通道数
		//for (int i = 0; i < 10; i++) {
		//	int offset = i * pixelSize;
		//	std::cout << "Pixel " << i << ": "
		//		<< "R: " << (int)_localBuffer[offset] << ", "
		//		<< "G: " << (int)_localBuffer[offset + 1] << ", "
		//		<< "B: " << (int)_localBuffer[offset + 2];
		//	if (pixelSize == 4) {
		//		std::cout << ", A: " << (int)_localBuffer[offset + 3];
		//	}
		//	std::cout << std::endl;
		//}
#endif // _DEBUG
		stbi_image_free(_localBuffer);
	}
}

Texture::Texture(unsigned int& id)
	: _id(0), _filePath(""), _localBuffer(nullptr), _width(0), _height(0), _BPP(0), type(aiTextureType::aiTextureType_NONE)
{
	glGenTextures(1, &this->_id);
	glBindTexture(GL_TEXTURE_2D, this->_id);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTextureID, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->_id, 0);
}

Texture::Texture(unsigned int width, unsigned int height, GLenum format)
	: _id(0), _filePath(""), _localBuffer(nullptr), _width(width), _height(height), _BPP(0), type(aiTextureType::aiTextureType_NONE)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &_id));
	//stbi_set_flip_vertically_on_load(0);
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot)); // OpenGL至少保证有16个纹理单元供使用，从GL_TEXTURE0到GL_TEXTRUE15。可以通过GL_TEXTURE0 + 8的方式获得GL_TEXTURE8
	GLCall(glBindTexture(GL_TEXTURE_2D, _id)); // 绑定这个纹理到当前激活的纹理单元，纹理单元GL_TEXTURE0默认总是被激活。
	// xxx 不知道需不需要重构。LearnOpenGL的 Mesh::Draw() 中，在  glActiveTexture 和  glBindTexture 中间调用的 glUniform1i，而我的实现做不到。或许可以传入个函数指针，在中间调用SetUniform？但SetUniform是泛型，写函数指针应该很难(都不知道是否可行)
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::LoadCubemap(const std::vector<std::string>& faces)
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		// stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			std::cout << "Cubemap texture succeed to load at path: " << faces[i] << std::endl;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture::LoadCubemap(const std::string& folderPath)
{
	std::vector<std::string> faces{};
	faces.push_back(folderPath + "/right.jpg");
	faces.push_back(folderPath + "/left.jpg");
	faces.push_back(folderPath + "/top.jpg");
	faces.push_back(folderPath + "/bottom.jpg");
	faces.push_back(folderPath + "/back.jpg");
	faces.push_back(folderPath + "/front.jpg");

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

	stbi_set_flip_vertically_on_load(0); // 天空盒不需要翻转

	int width, height, nrChannels;

	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			std::cout << "Cubemap texture succeed to load at path: " << faces[i] << std::endl;
			

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
