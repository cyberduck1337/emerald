#include "Transform.hpp"
#include "glm/ext.hpp"

namespace Emerald::ECS
{
    glm::vec3 Transform::eulerAngles() const
    {
        return glm::degrees(glm::eulerAngles(glm::normalize(m_rotation)));
    }

    glm::vec3 Transform::direction() const
    {
        const glm::vec3 rot = eulerAngles();

        return {
            glm::cos(glm::radians(rot.x)) * glm::cos(glm::radians(rot.y)),
            glm::sin(glm::radians(rot.y)),
            glm::sin(glm::radians(rot.x)) * glm::cos(glm::radians(rot.y))
        };
    }

    glm::vec3 Transform::front() const
    {
        return glm::normalize(direction());
    }

    glm::vec3 Transform::right() const
    {
        return glm::normalize(glm::cross(VECTOR_UP, front()));
    }

    glm::vec3 Transform::up() const
    {
        return glm::normalize(glm::cross(right(), front()));
    }

    void Transform::rotate(const glm::vec3& eulerAngles)
    {
        glm::quat eulerRot = glm::quat(glm::radians(eulerAngles));
        m_rotation *= glm::inverse(m_rotation) * eulerRot * m_rotation;
    }

    glm::mat4 Transform::model() const
    {
        return (glm::translate(m_position) * glm::toMat4(m_rotation) * glm::scale(m_scale));
    }
}
