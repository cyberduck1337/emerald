#pragma once

#include "glm/mat4x4.hpp"

namespace Emerald
{
    class CameraComponent
    {
    public:
        CameraComponent(float fov, float near, float far);

    public:
        float m_fov;
        float m_near;
        float m_far;

        glm::mat4 m_view;
        glm::mat4 m_projection;
    };
}
