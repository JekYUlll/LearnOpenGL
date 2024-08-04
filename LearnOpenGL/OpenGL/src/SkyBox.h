#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include "Texture.h"
#include "Shader.h"
#include "Math.h"
#include "Camera.h"
#include "config.h"

class Skybox : public Entity {
public:
    Skybox(const std::vector<std::string>& faces);
    Skybox(const std::string& folderPath);
    void Draw(const Shader& shader, const Camera& camera);
    virtual void Update(float deltaTime) override;
    std::shared_ptr<Texture> _texture;

private:
    unsigned int _skyboxVAO, _skyboxVBO;
    void LoadSkybox(const std::vector<std::string>& faces);
    void LoadSkybox(const std::string& folderPath);
};
