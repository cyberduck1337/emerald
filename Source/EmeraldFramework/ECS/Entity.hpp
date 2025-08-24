#pragma once

#include "entt/entt.hpp"
#include "Components/Transform.hpp"
#include <string>

namespace Emerald::ECS
{
    class Entity
    {
    public:
        static Entity instantiate(const std::string& name);
        static Entity instantiate(const std::string& name, Transform transform);
        static Entity instantiate(const std::string& name, Transform transform, Entity parent);

        Entity(entt::entity handle);

        operator entt::entity() const;

    private:
        entt::entity m_handle;
    };
}
