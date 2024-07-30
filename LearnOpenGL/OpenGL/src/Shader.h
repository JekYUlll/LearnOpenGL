#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "config.h"
#include "Debug.h"
#include "glm/glm.hpp"

struct ShaderProgramSources
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int _rendererID;
    std::string _filepath;
    mutable std::unordered_map<std::string, int> _uniformLocationCache; // 存储uniform变量的location，防止多次重复获取
public:
    // 构造器读取并构建着色器(传入单个文件路径)
    Shader(const std::string& filepath);
    // 传入vertex和fragment的路径
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // 直接用字符串形式传入shader
    Shader(const std::string& vertexShader, const std::string& fragmentShader, bool isDirect);
    ~Shader();

    void Use() const;
    void UnUse() const;

    template <typename T>
    void SetUniform(const std::string& name, const T& value) const;

    void SetUniform(const std::string& name, float v0, float v1, float v2) const;
    void SetUniform(const std::string& name, float v0, float v1, float v2, float v3) const;

    void PrintShader(const std::string& vertexShader, const std::string& fragmentShader) const; // 自己加的，打印shader

private:
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name) const;
    ShaderProgramSources ReadShader(const std::string& filepath); //cherno为ParseShader，此处改为read，并加入重载版本
    ShaderProgramSources ReadShader(const GLchar* vertexPath, const GLchar* fragmentPath); // 分别从两个路径读取
    unsigned int CompileShader(unsigned int type, const std::string& source);

    void GLCheckError() const;
    std::string GetErrorString(GLenum error) const;
};

#endif // !SHADER_H
