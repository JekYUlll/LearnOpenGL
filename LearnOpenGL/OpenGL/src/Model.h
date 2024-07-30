#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <vector>

#include "Mesh.h"

class Model
{
public:
    Model(const char* path);

    void Draw(const Shader& shader);

private:
    std::vector<std::shared_ptr<Texture>> textures_loaded; // 优化：存储已经加载过的纹理，防止重复加载
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
};

#endif // !MODEL_H

