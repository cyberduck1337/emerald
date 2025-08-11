#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Emerald::ECS
{
    class Transform
    {
        static constexpr glm::vec3 VECTOR_UP = { 0.0f, 1.0f, 0.0f };
        static constexpr glm::vec3 VECTOR_FRONT = { 0.0f, 0.0f, -1.0f };

    public:
        glm::vec3 eulerAngles() const;
        glm::vec3 direction() const;
        glm::vec3 front() const;
        glm::vec3 right() const;
        glm::vec3 up() const;

        void rotate(const glm::vec3& eulerAngles);

        glm::mat4 model() const;

    public:
        glm::vec3 m_position;
        glm::quat m_rotation;
        glm::vec3 m_scale;
    };
}
