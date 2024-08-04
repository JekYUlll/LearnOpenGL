#pragma once
#include"Component.h"

class Collision : public Component {
public:
    void Update(float deltaTime) override {
        // ÊµÏÖÅö×²Âß¼­
    }

    bool CheckCollision(const Collision& other) const {
        // Åö×²¼ì²âÂß¼­
    }
};
