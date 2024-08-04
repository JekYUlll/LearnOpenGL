#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include "Component.h"

class Component;

class Entity
{
public:
	virtual void Update(float deltaTime);

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args) {
        T* component(new T(std::forward<TArgs>(args)...));
        component->SetOwner(this);
        std::unique_ptr<Component> uPtr(component);
        _components.emplace_back(std::move(uPtr));
        _componentTypeMap[std::type_index(typeid(T))] = component;
        return *component;
    }

    template <typename T>
    T* GetComponent() {
        auto it = _componentTypeMap.find(std::type_index(typeid(T)));
        if (it != _componentTypeMap.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

private:
    std::vector<std::unique_ptr<Component>> _components;
    std::unordered_map<std::type_index, Component*> _componentTypeMap;

};
