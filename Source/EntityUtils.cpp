#include "EntityUtils.hpp"

#include "Components/NameComponent.hpp"
#include "Scene.hpp"

namespace Emerald
{
    Entity EntityUtils::instantiate(const std::string& name, const Transform& transform)
    {
        Scene& scene = Scene::get();

        entt::entity entity = scene.m_registry.create();

        addComponent<Transform>(entity, transform);
        addComponent<NameComponent>(entity, name);

        return entity;
    }

    Entity EntityUtils::instantiate(const std::string& name, const glm::vec3& position)
    {
        return instantiate(name, { position, {}, { 1.0f, 1.0f, 1.0f } });
    }

    Entity EntityUtils::instantiate(const std::string& name)
    {
        return instantiate(name, { {}, {}, { 1.0f, 1.0f, 1.0f } });
    }
} // namespace Emerald
