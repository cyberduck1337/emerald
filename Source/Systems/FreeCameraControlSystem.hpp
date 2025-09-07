#pragma once

#include "Components/FreeCameraComponent.hpp"
#include "Entity.hpp"
#include "System.hpp"

namespace Emerald
{
    class FreeCameraControlSystem final : public System<Transform, const FreeCameraComponent>
    {
    public:
        FreeCameraControlSystem();

        void update(Entity entity) override;

    private:
        glm::vec2 m_lastMousePosition;
    };
} // namespace Emerald
