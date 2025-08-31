#pragma once

#include "Entity.hpp"
#include "SystemBase.hpp"

namespace Emerald
{
    template<typename... Components>
    class System : public SystemBase
    {
    public:
        virtual void update(Entity entity) = 0;

    private:
        void update(entt::registry& registry) override
        {
            for(auto&& entity : registry.view<Components...>())
            {
                const Entity e{entity};
                update(e);
            }
        }
    };
}
