#pragma once

#include "Entity.hpp"
#include "SystemBase.hpp"

namespace Emerald
{
    template<typename DerivedType, typename... Components>
    class System : public SystemBase
    {
    private:
        void update(entt::registry& registry) final
        {
            auto* derived = static_cast<DerivedType*>(this);
            auto view = registry.view<Components...>();

            view.each([derived]<typename... Ts>(const entt::entity entity, Ts&&... components)
            {
                const Entity e{entity};
                derived->update(e, std::forward<Ts>(components)...);
            });
        }
    };
}
