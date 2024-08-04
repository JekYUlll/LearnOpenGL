#pragma once
#include "Component.h"

class Movement : public Component {
public:
    Movement(float speed) : speed(speed) {}

    void Update(float deltaTime) override;

private:
    float speed;
};
