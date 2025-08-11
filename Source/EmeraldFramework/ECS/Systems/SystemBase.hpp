#pragma once

#include "entt/entt.hpp"

namespace Emerald::ECS
{
    class SystemBase
    {
    public:
        virtual ~SystemBase() = default;
        virtual void update(entt::registry& registry) = 0;
    };
}
