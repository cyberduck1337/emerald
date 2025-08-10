#pragma once

#include "entt/entt.hpp"

namespace Emerald::ECS
{
    class System
    {
    public:
        virtual ~System() = default;
        virtual void update(entt::registry& registry) = 0;
    };
}
