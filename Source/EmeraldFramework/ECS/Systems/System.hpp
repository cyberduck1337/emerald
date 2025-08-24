#pragma once

#include "SystemBase.hpp"
#include "ECS/Entity.hpp"

namespace Emerald::ECS
{
    template<typename... Components>
    class System : public SystemBase
    {
    public:
        virtual void update(Entity entity) = 0;

    private:
        virtual void update(entt::registry& registry) final override;
    };
}
