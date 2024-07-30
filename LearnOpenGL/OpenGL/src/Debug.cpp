#include "Debug.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const GLchar* function, const GLchar* file, GLint line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << " : " << line << std::endl;
        return false;
    }
    return true;
    // 调用的时候 ASSERT(GLLogCall()); 如果返回false，就会中断调试器。
}

#ifdef _DEBUG
void DEBUG_Texture(int i)
{
    GLint textureID, activeTextureUnit;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &activeTextureUnit);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &textureID);
    std::cout << "Texture unit: " << i
        << " - Active Texture Unit: " << activeTextureUnit - GL_TEXTURE0
        << ", Currently bound 2D texture: " << textureID << std::endl;
}
#else 
void DEBUG_Texture() {}
#endif // _DEBUG

