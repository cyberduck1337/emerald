#pragma once

#include "entt/entt.hpp"

namespace Emerald::ECS
{
    class System
    {
    public:
        virtual void update(entt::registry& registry) = 0;
    };
}
