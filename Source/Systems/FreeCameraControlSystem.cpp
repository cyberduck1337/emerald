#include "FreeCameraControlSystem.hpp"

#include "Components/FreeCameraComponent.hpp"
#include "Gfx.hpp"
#include "Input.hpp"

namespace Emerald
{
    FreeCameraControlSystem::FreeCameraControlSystem() : m_lastMousePosition()
    {
    }

    void FreeCameraControlSystem::update(Entity entity, Transform& transform, const FreeCameraComponent camera)
    {
        const float speed = camera.speed();
        const float sensitivity = camera.sensitivity();

        const glm::vec2 mousePosition = Input::getMousePosition();

        if (Input::getKeyDown(Input::KeyCode::W))
        {
            transform.m_position += camera.speed() * Gfx::deltaTime() * transform.front();
        }

        if (Input::getKeyDown(Input::KeyCode::S))
        {
            transform.m_position -= speed * Gfx::deltaTime() * transform.front();
        }

        if (Input::getKeyDown(Input::KeyCode::A))
        {
            transform.m_position -= glm::normalize(glm::cross(transform.front(), transform.up())) * speed * Gfx::deltaTime();
        }

        if (Input::getKeyDown(Input::KeyCode::D))
        {
            transform.m_position += glm::normalize(glm::cross(transform.front(), transform.up())) * speed * Gfx::deltaTime();
        }

        if (Input::getKeyDown(Input::KeyCode::SPACE))
        {
            transform.m_position += speed * Gfx::deltaTime() * transform.up();
        }

        if (Input::getKeyDown(Input::KeyCode::LEFT_CONTROL))
        {
            transform.m_position -= speed * Gfx::deltaTime() * transform.up();
        }

        if (Input::getMouseButtonDown(Input::MouseButton::RIGHT))
        {
            const float xOffset = (m_lastMousePosition.x - mousePosition.x) * sensitivity;
            const float yOffset = (mousePosition.y - m_lastMousePosition.y) * sensitivity;

            glm::vec3 eulerAngles = transform.eulerAngles();
            eulerAngles.x += xOffset;
            eulerAngles.y += yOffset;
            eulerAngles.y = glm::clamp(eulerAngles.y, -89.0f, 89.0f);

            transform.m_rotation = glm::quat(glm::radians(eulerAngles));
        }

        m_lastMousePosition = mousePosition;
    }
} // namespace Emerald
