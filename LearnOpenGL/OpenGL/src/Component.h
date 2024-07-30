#pragma once

class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float deltaTime) = 0;
};
