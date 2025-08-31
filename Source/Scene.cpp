#include "Scene.hpp"

#include <utility>

#include "Components/NameComponent.hpp"
#include "Entity.hpp"

namespace Emerald
{
    Scene::Scene(std::string name) : m_name(std::move(name))
    {
    }

    Scene::~Scene()
    {
        for(const entt::entity entity : Entity::g_registry.view<Transform>())
        {
            Entity::g_registry.destroy(entity);
        }
    }

    void Scene::update()
    {
        for (auto&& system : m_systems)
        {
            system->update(Entity::g_registry);
        }
    }
} // namespace Emerald
