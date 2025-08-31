#pragma once

#include <string>

#include "Assertion.hpp"
#include "Components/Transform.hpp"
#include "entt/entt.hpp"

namespace Emerald
{
    class Entity
    {
        friend class Scene;

    public:
        static Entity instantiate(const std::string& name);
        static Entity instantiate(const std::string& name, const Transform& transform);

        explicit Entity(entt::entity handle);
        explicit operator entt::entity() const;

        template<typename T, typename... Args>
        void addComponent(Args&&... args)
        {
            g_registry.emplace_or_replace<T>(m_handle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& getComponent()
        {
            T* component = g_registry.try_get<T>(m_handle);
            EMERALD_VERIFY_THROW(component != nullptr, std::runtime_error, "Attempt to get nonexistent component!");

            return *component;
        }

        template<typename T>
        void removeComponent() const
        {
            g_registry.remove<T>(m_handle);
        }

    private:
        static inline entt::registry g_registry;
        entt::entity m_handle;
    };
} // namespace Emerald
