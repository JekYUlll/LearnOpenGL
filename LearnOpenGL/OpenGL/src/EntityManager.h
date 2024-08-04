#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include "Entity.h"

class EntityManager {
public:
    Entity& CreateEntity();

    void UpdateAllEntities(float deltaTime);

    void RemoveEntity(Entity* entity);

    void Clear();

private:
    std::vector<std::unique_ptr<Entity>> entities;
};

