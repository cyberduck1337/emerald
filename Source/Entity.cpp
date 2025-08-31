#include "Entity.hpp"

#include "Components/NameComponent.hpp"

namespace Emerald
{
    Entity Entity::instantiate(const std::string& name)
    {
        return instantiate(name, {});
    }

    Entity Entity::instantiate(const std::string& name, const Transform& transform)
    {
        const entt::entity handle = g_registry.create();
        Entity entity{handle};

        entity.addComponent<Transform>(transform);
        entity.addComponent<NameComponent>(name);

        return entity;
    }

    Entity::Entity(const entt::entity handle)
    {
        m_handle = handle;
    }

    Entity::operator entt::entity() const
    {
        return m_handle;
    }
} // namespace Emerald::ECS
