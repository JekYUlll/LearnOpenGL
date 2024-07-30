#shader vertex --------------------------------
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

#shader fragment --------------------------------
#version 330 core

out vec4 color;

in vec3 objectColor;
in vec2 TexCoord;
in float TexIndex;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material material;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 pureObjectColor;
uniform int debugMode; // 0: normal, 1: visualize normal, 2: visualize frag position
uniform bool showTexture;

void main()
{
    vec4 texColor1 = texture(ourTexture1, TexCoord);
    vec4 texColor2 = texture(ourTexture2, TexCoord);
    vec4 lightColor_v4 = vec4(lightColor, 1.0f);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear*distance +light.quadratic*(distance*distance));

    if (debugMode == 0)
    {
        vec3 diffuseTex;
        vec3 specularTex;
        vec3 emissionTex;

        if (showTexture) {
            diffuseTex = vec3(texture(material.diffuse, TexCoord));
            specularTex = vec3(texture(material.specular, TexCoord));
            emissionTex = vec3(texture(material.emission, TexCoord));
        } else {
            diffuseTex = pureObjectColor;
            specularTex = pureObjectColor;
        }
        // Ambient
        vec3 ambient = light.ambient * diffuseTex;
        // Diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * diffuseTex;
        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * specularTex;

        vec3 emission = 0.2f * (1.0f - emissionTex);
        
        color = vec4(ambient + diffuse + specular + emission, 1.0f);
        
    }
    else if (debugMode == 1) 
    {
        // 可视化法线
        vec3 norm = normalize(Normal);
        vec3 debugColor = (norm * 0.5) + 0.5;
        color = vec4(debugColor, 1.0f);
    } 
    else if (debugMode == 2) 
    {
        // 可视化片段位置
        vec3 debugColor = min(FragPos, 1.0);
        color = vec4(debugColor, 1.0f);
    }


}