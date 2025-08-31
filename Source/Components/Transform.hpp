#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Emerald
{
    class Transform final
    {
        static constexpr glm::vec3 VECTOR_UP = { 0.0f, 1.0f, 0.0f };
        static constexpr glm::vec3 VECTOR_FRONT = { 0.0f, 0.0f, -1.0f };

    public:
        Transform();
        Transform(const glm::vec3& m_position, const glm::quat& m_rotation, const glm::vec3& m_scale);

        [[nodiscard]]
        glm::vec3 eulerAngles() const;

        [[nodiscard]]
        glm::vec3 direction() const;

        [[nodiscard]]
        glm::vec3 front() const;

        [[nodiscard]]
        glm::vec3 right() const;

        [[nodiscard]]
        glm::vec3 up() const;

        [[nodiscard]]
        glm::mat4 model() const;

        void rotate(const glm::vec3& eulerAngles);

    public:
        glm::vec3 m_position;
        glm::quat m_rotation;
        glm::vec3 m_scale;
    };
}
