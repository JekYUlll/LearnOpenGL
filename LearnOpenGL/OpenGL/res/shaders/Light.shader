#shader vertex --------------------------------
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;
layout(location = 3) in float aTexIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}

#shader fragment --------------------------------
#version 330 core

out vec4 color;

uniform vec3 lightColor;

void main()
{
    color = vec4(lightColor, 1.0f);
}