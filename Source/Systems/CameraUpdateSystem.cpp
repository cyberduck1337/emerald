#include "CameraUpdateSystem.hpp"

#include "Gfx.hpp"

namespace Emerald
{
    void CameraUpdateSystem::update(Entity entity, const Transform& transform, CameraComponent& camera)
    {
        const glm::uvec2 windowSize = Gfx::getWindowSize();

        camera.m_projection = glm::perspective(glm::radians(camera.m_fov), static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y), camera.m_near, camera.m_far);
        camera.m_view = glm::lookAt(transform.m_position, transform.m_position + transform.front(), transform.up());
    }
} // namespace Emerald
