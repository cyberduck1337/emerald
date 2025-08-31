#pragma once

#include "entt/entt.hpp"

namespace Emerald
{
    class SystemBase
    {
    public:
        virtual ~SystemBase() = default;
        virtual void update(entt::registry& registry) = 0;
    };
}
