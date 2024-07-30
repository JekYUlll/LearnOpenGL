#include "Shader.h"

Shader::Shader(const std::string& filepath)
	: _filepath(filepath), _rendererID(0)
{
    ShaderProgramSources source = ReadShader(filepath);
    this->_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
#ifdef _DEBUG
    std::cout << "Shader created with ID: " << _rendererID << std::endl;
#endif // _DEBUG
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    ShaderProgramSources source = ReadShader(vertexPath, fragmentPath);
    this->_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, bool isDirect)
    : _filepath(""), _rendererID(0)
{
    ShaderProgramSources source = { vertexShader, fragmentShader };
    this->_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
#ifdef _DEBUG
    std::cerr << "[shader distroyed]" << std::endl;
#endif // _DEBUG
    GLCall(glDeleteProgram(this->_rendererID));
}

// 读取并切分shader文件
ShaderProgramSources Shader::ReadShader(const std::string& filepath)
{
    std::ifstream stream(filepath); //
    if (!stream)
        throw std::runtime_error("Failed to open shader file: " + filepath);
    stream.exceptions(std::ifstream::badbit); // stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);会无差别在末尾抛出异常
    
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

	try {
		static unsigned int lineNum = 0; // 行数，debug用
		while (std::getline(stream, line))
		{
			lineNum++;

			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos) {
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos) {
					type = ShaderType::FRAGMENT;
				}
			}
			else {
				ss[(int)type] << line << '\n';
			}
		}
	}
	catch (const std::ifstream::failure& e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cerr << "Failed to read shader file: " << filepath << std::endl;
		std::cerr << e.what() << std::endl;
		throw std::runtime_error("Shader file read error: " + filepath);
	}
    return { ss[0].str(), ss[1].str() };
}

ShaderProgramSources Shader::ReadShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return { vertexCode, fragmentCode };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

void Shader::GLCheckError() const
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "[OpenGL Error] (" << error << "): " << GetErrorString(error) << std::endl;
    }
}

std::string Shader::GetErrorString(GLenum error) const
{
    switch (error) {
    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default: return "Unknown Error";
    }
}

void Shader::PrintShader(const std::string& vertexShader, const std::string& fragmentShader) const
{
#ifdef PRINT_SHADER
    std::cout << "[VERTEX]" << std::endl;
    std::cout << vertexShader << std::endl;
    std::cout << "[FRAGMENT]" << std::endl;
    std::cout << fragmentShader << std::endl;
#else 
    return;
#endif // !PRINT_SHADER
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(shaderProgram, vs));
    GLCall(glAttachShader(shaderProgram, fs));
    GLCall(glLinkProgram(shaderProgram));
    GLCall(glValidateProgram(shaderProgram));

    PrintShader(vertexShader, fragmentShader);

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return shaderProgram;
}

void Shader::Use() const
{
    GLCall(glUseProgram(_rendererID));

    GLCheckError();
#ifdef _DEBUG
    /*GLint currentProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (currentProgram != this->_rendererID) {
        std::cerr << "Failed to use shader program ID: " << _rendererID << std::endl;
    }*/
#endif // _DEBUG
}

void Shader::UnUse() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform(const std::string& name, float v0, float v1, float v2) const
{
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform(const std::string& name, float v0, float v1, float v2, float v3) const
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

template<>
void Shader::SetUniform<int>(const std::string& name, const int& value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

template<>
void Shader::SetUniform<unsigned int>(const std::string& name, const unsigned int& value) const
{
    glUniform1i(GetUniformLocation(name), static_cast<unsigned int>(value)); // 正确性存疑
}

template<>
void Shader::SetUniform<float>(const std::string& name, const float& value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

template<>
void Shader::SetUniform<bool>(const std::string& name, const bool& value) const
{
    glUniform1i(GetUniformLocation(name), (int)value);
}

template<>
void Shader::SetUniform<glm::vec2>(const std::string& name, const glm::vec2& value) const
{
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

template<>
void Shader::SetUniform<glm::vec3>(const std::string& name, const glm::vec3& value) const
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

template<>
void Shader::SetUniform<glm::vec4>(const std::string& name, const glm::vec4& value) const
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

template<>
void Shader::SetUniform<glm::mat3>(const std::string& name, const glm::mat3& matrix) const
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

template<>
void Shader::SetUniform<glm::mat4>(const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(this->_rendererID, name.c_str()));

    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exit! " << std::endl; // 但即使是-1，也可以写入map中
    
    _uniformLocationCache[name] = location;
    return location;
}


