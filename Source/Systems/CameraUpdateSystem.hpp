#pragma once

#include "Components/CameraComponent.hpp"
#include "System.hpp"

namespace Emerald
{
    class CameraUpdateSystem final : public System<CameraUpdateSystem, const Transform, CameraComponent>
    {
    public:
        void update(Entity entity, const Transform& transform, CameraComponent& camera);
    };
} // namespace Emerald
