#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<Texture>>& textures)
    : vertices(vertices), indices(indices), textures(textures)
{
    _VAO = std::make_unique<VertexArray>();
    _VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
    _IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());
    _VAO->Bind();
    _VBO->Bind();
    _IBO->Bind();
    // ÈßÓà£¬²âÊÔ
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
    VertexBufferLayout layout = VertexLayoutBuilder<Vertex>::Build();
    _VAO->AddBuffer(*_VBO, layout);
    _VAO->UnBind();
    _VBO->UnBind();
    _IBO->UnBind();
}

void Mesh::Draw(const Shader& shader) const
{
    unsigned int difNum = 0;
    unsigned int norNum = 0;
    unsigned int speNum = 0;
    shader.Use();

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        if (glIsTexture(textures[i]->GetID()) == GL_FALSE) {
            std::cerr << "Texture ID is not valid for texture " << i << std::endl;
        }
        textures[i]->Bind(i);

        switch (textures[i]->type)
        {
        case aiTextureType::aiTextureType_NONE:
            std::cerr << "Texture " << i << " has no type!" << std::endl;
            break;
        case aiTextureType::aiTextureType_DIFFUSE:
            difNum++;
            shader.SetUniform<int>("texture_diffuse" + std::to_string(difNum), i);
            break;
        case aiTextureType::aiTextureType_NORMALS:
            norNum++;
            shader.SetUniform<int>("texture_normal" + std::to_string(norNum), i);
            break;
        case aiTextureType::aiTextureType_SPECULAR:
            speNum++;
            shader.SetUniform<int>("texture_specular" + std::to_string(speNum), i);
            break;
        default:
            break;
        }
    }

    shader.SetUniform<float>("material.shininess", 16.0f);

    _VAO->Bind();
    Renderer::getInstance().DrawElements(*_VAO, *_IBO, shader);
    _VAO->UnBind();
    
    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        textures[i]->UnBind();
    }
}




