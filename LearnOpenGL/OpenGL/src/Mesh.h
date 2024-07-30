#ifndef MESH_H
#define MESH_H

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Debug.h"
#include "Math.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

template<typename T>
struct VertexLayoutBuilder;

template<>
struct VertexLayoutBuilder<Vertex>
{
    static VertexBufferLayout Build()
    {
        VertexBufferLayout layout;
        layout.Push<glm::vec3>(1); // Position // 此部分在教程中的 Mesh::setupMesh() 中实现
        layout.Push<glm::vec3>(1); // Normal
        layout.Push<glm::vec2>(1); // TexCoords
        return layout;
    }
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<Texture>>& textures);

    void Draw(const Shader& shader) const;

private:
    std::unique_ptr<VertexArray> _VAO;
    std::unique_ptr<VertexBuffer> _VBO;
    std::unique_ptr<IndexBuffer> _IBO;
};

#endif //!MESH_H
