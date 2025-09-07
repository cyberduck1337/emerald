#include "FreeCameraComponent.hpp"

namespace Emerald
{
    FreeCameraComponent::FreeCameraComponent(const float speed, const float sensitivity) : m_speed(speed), m_sensitivity(sensitivity)
    {
    }

    float FreeCameraComponent::speed() const
    {
        return m_speed;
    }

    float FreeCameraComponent::sensitivity() const
    {
        return m_sensitivity;
    }
} // namespace Emerald
