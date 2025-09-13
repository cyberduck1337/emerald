#include "Scene.hpp"

#include <utility>

#include "Assertion.hpp"
#include "Components/NameComponent.hpp"
#include "Components/Transform.hpp"

namespace Emerald
{
    Scene::Scene()
    {
        EMERALD_VERIFY_THROW(g_instance == nullptr, std::runtime_error, "Scene::g_instance already initialized!");
        g_instance = this;
    }

    Scene::~Scene()
    {
        for(const entt::entity entity : m_registry.view<Transform>())
        {
            m_registry.destroy(entity);
        }

        g_instance = nullptr;
    }

    Scene& Scene::get()
    {
        EMERALD_VERIFY_THROW(g_instance != nullptr, std::runtime_error, "Scene::g_instance has not been initialized yet!");
        return *g_instance;
    }

    void Scene::update()
    {
        for (auto&& system : m_systems)
        {
            system->update(m_registry);
        }
    }
} // namespace Emerald
