#pragma once
#include "Component.h"
#include "Math.h"

class Transform : public Component {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform()
        : position(0.0f), rotation(0.0f), scale(1.0f) {}

    void Update(float deltaTime) override {
        // ¸üÐÂÂß¼­
    }
};