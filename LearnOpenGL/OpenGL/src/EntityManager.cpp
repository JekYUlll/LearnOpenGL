#include "EntityManager.h"

Entity& EntityManager::CreateEntity() {
    std::unique_ptr<Entity> entity = std::make_unique<Entity>();
    entities.emplace_back(std::move(entity));
    return *entities.back();
}

void EntityManager::UpdateAllEntities(float deltaTime) {
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::RemoveEntity(Entity* entity) {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [&](const std::unique_ptr<Entity>& e) { return e.get() == entity; }),
        entities.end());
}

void EntityManager::Clear() {
    entities.clear();
}