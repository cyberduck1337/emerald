#include "Scene.hpp"

#include <utility>

#include "Assertion.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/NameComponent.hpp"
#include "Components/Transform.hpp"
#include "EntityUtils.hpp"
#include "Gfx.hpp"

namespace Emerald
{
    Scene::Scene()
    {
        EMERALD_VERIFY_THROW(g_instance == nullptr, std::runtime_error, "Scene::g_instance already initialized!");
        g_instance = this;

        Transform mainCameraInitialTransform{};
        mainCameraInitialTransform.m_position = {0.0f, 0.0f, -2.5f};
        mainCameraInitialTransform.m_rotation = glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 0.0f)));

        m_camera = EntityUtils::instantiate("MainCamera", mainCameraInitialTransform);
        EntityUtils::addComponent<CameraComponent>(m_camera, 45.0f, 0.1f, 100.0f);
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

        // scene camera update
        {
            const glm::uvec2 windowSize = Gfx::getWindowSize();

            const Transform& cameraTransform = EntityUtils::getComponent<Transform>(m_camera);
            CameraComponent& cameraComponent = EntityUtils::getComponent<CameraComponent>(m_camera);

            cameraComponent.m_projection = glm::perspective(glm::radians(cameraComponent.m_fov), static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y), cameraComponent.m_near, cameraComponent.m_far);
            cameraComponent.m_view = glm::lookAt(cameraTransform.m_position, cameraTransform.m_position + cameraTransform.front(), cameraTransform.up());
        }
    }

    Entity Scene::getCameraObject() const noexcept
    {
        return m_camera;
    }
} // namespace Emerald
