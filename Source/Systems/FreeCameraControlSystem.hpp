#pragma once

#include "Components/FreeCameraComponent.hpp"
#include "EntityUtils.hpp"
#include "System.hpp"

namespace Emerald
{
    class FreeCameraControlSystem final : public System<FreeCameraControlSystem, Transform, const FreeCameraComponent>
    {
    public:
        FreeCameraControlSystem();

        void update(Entity entity, Transform& transform, FreeCameraComponent camera);

    private:
        glm::vec2 m_lastMousePosition;
    };
} // namespace Emerald
