#pragma once

#include "Assertion.hpp"
#include "Entity.hpp"
#include "Components/Transform.hpp"
#include "Scene.hpp"
#include "fmt/format.h"

#include <string>
#include <stdexcept>

namespace Emerald
{
    class EntityUtils
    {
    public:
        EntityUtils() = delete;
        ~EntityUtils() = delete;

        static Entity instantiate(const std::string& name, const Transform& transform);
        static Entity instantiate(const std::string& name, const glm::vec3& position);
        static Entity instantiate(const std::string& name);

        template<typename... Args>
        static void addComponent(std::string_view name, Args&&... args)
        {
            const entt::hashed_string hs{ name.data() };
            entt::meta_type componentMetaType = entt::resolve(hs);
            EMERALD_VERIFY_THROW(componentMetaType, std::runtime_error, fmt::format("Failed to resolve component type \'{}\'", name));
            componentMetaType.construct(std::forward<Args>(args)...);
        }

        template<typename T, typename... Args>
        static T& addComponent(Entity entity, Args&&... args)
        {
            return Scene::get().m_registry.emplace_or_replace<T>(entity, std::forward<Args>(args)...);
        }

        template<typename T>
        static bool hasComponent(Entity entity)
        {
            return Scene::get().m_registry.try_get<T>(entity) != nullptr;
        }

        template<typename T>
        static T& getComponent(Entity entity)
        {
            T* component = Scene::get().m_registry.try_get<T>(entity);
            EMERALD_VERIFY_THROW(component != nullptr, std::runtime_error, "Attempt to get nonexistent component!");

            return *component;
        }
    };
}
