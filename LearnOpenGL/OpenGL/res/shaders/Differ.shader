#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexIndex;

out vec3 ourColor;
out vec2 TexCoord;
out float TexIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// uniform mat4 u_MVP;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    ourColor = aColor;
    TexCoord = aTexCoord;
    TexIndex = aTexIndex;
}

#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in float TexIndex;

// uniform sampler2D ourTexture1;
// uniform sampler2D ourTexture2; 
uniform sampler2D ourTexture3; // calm
uniform sampler2D Textures[3];

void main()
{
    // vec4 texColor1 = texture(ourTexture1, TexCoord);
    // vec4 texColor2 = texture(ourTexture2, TexCoord);
    vec4 texColor3 = texture(ourTexture3, TexCoord);
    vec4 TexColor;
    // if(TexIndex == 0.0f) 
    //     TexColor = texColor1;
    // else 
    //     TexColor = texColor2;
    int index = int(TexIndex);
    TexColor = texture(Textures[index], TexCoord);
    vec4 mixedColor = mix(TexColor, texColor3, 0.2) * vec4(ourColor, 1.0);
    FragColor = mixedColor;
}