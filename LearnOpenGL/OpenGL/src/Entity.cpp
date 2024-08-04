#include "Entity.h"

void Entity::Update(float deltaTime)
{
    for (auto& component : _components) {
        component->Update(deltaTime);
    }
}