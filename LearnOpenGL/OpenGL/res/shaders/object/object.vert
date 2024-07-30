#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;
layout(location = 4) in float aTexIndex;

out vec3 objectColor;
out vec2 TexCoord;
out float TexIndex;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    objectColor = aColor;
    TexCoord = aTexCoord;
    TexIndex = aTexIndex;
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal; // 更新法线(转换到世界空间)
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}