#include "CameraComponent.hpp"

namespace Emerald
{
    CameraComponent::CameraComponent(const float fov, const float near, const float far) : m_fov(fov), m_near(near), m_far(far), m_view(), m_projection()
    {
    }
} // namespace Emerald
