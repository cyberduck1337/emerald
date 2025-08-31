#pragma once

#include "Components/CameraComponent.hpp"
#include "System.hpp"

namespace Emerald
{
    class CameraUpdateSystem final : public System<Transform, CameraComponent>
    {
    public:
        void update(Entity entity) override;
    };
} // namespace Emerald
