#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <GL/glew.h>
// 断言(assertion) __debugbreak 是 msvc 的 Cherno 将此部分放在Renderer.h中
#ifdef _DEBUG

#ifdef _MSC_VER
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#define ASSERT(x) x;
#endif // _MSC_VER

#define FUNC_CALL std::cout << __func__ << "Called" << std::endl

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const GLchar * function, const GLchar * file, GLint line);

#else
#define ASSERT(x) x;
#define GLCall(x) x;
#define FUNC_CALL

#endif // _DEBUG

void DEBUG_Texture(int i);



#endif // !DEBUG_HPP



