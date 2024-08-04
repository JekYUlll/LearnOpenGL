#pragma once
#include "Entity.h"

class Entity;

class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float deltaTime) = 0;

    inline void SetOwner(Entity* owner) { this->owner = owner; }

protected:
    Entity* owner;
};
