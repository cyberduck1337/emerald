#include "Game.hpp"
#include "Input.hpp"
#include "Gfx.hpp"
#include "System.hpp"
#include "entt/entity/fwd.hpp"

class FlyCameraComponent
{
public:
    FlyCameraComponent(float speed, float sensetivity) : m_speed(speed), m_sensetivity(sensetivity)
    {
    }

public:
    float m_speed;
    float m_sensetivity;
};

class FlyCameraSystem : public Emerald::ECS::System
{
public:
    virtual void update(entt::registry& registry) override final
    {
        auto view = registry.view<Emerald::Gfx::Transform, Emerald::Gfx::Camera, const FlyCameraComponent>();
        for(auto&& [entity, transform, camera, freeCameraComponent] : view.each())
        {
            if(Emerald::Input::getKeyDown(Emerald::Input::KeyCode::W))
            {
                transform.position += freeCameraComponent.m_speed * Emerald::Gfx::deltaTime() * transform.front();
            }

            if(Emerald::Input::getKeyDown(Emerald::Input::KeyCode::S))
            {
                transform.position -= freeCameraComponent.m_speed * Emerald::Gfx::deltaTime() * transform.front();
            }

            if(Emerald::Input::getKeyDown(Emerald::Input::KeyCode::A))
            {
                transform.position -= glm::normalize(glm::cross(transform.front(), transform.up())) * freeCameraComponent.m_speed * Emerald::Gfx::deltaTime();
            }

            if(Emerald::Input::getKeyDown(Emerald::Input::KeyCode::D))
            {
                transform.position += glm::normalize(glm::cross(transform.front(), transform.up())) * freeCameraComponent.m_speed * Emerald::Gfx::deltaTime();
            }

            if(Emerald::Input::getKeyDown(Emerald::Input::KeyCode::SPACE))
            {
                transform.position += freeCameraComponent.m_speed * Emerald::Gfx::deltaTime() * transform.up();
            }

            if(Emerald::Input::getKeyDown(Emerald::Input::KeyCode::LEFT_CONTROL))
            {
                transform.position -= freeCameraComponent.m_speed * Emerald::Gfx::deltaTime() * transform.up();
            }

            if(Emerald::Input::getMouseButtonDown(1))
            {
                const glm::vec2 mousePosition = Emerald::Input::getMousePosition();

                float xoffset = (m_lastMousePosition.x - mousePosition.x) * freeCameraComponent.m_sensetivity;
                float yoffset = (mousePosition.y - m_lastMousePosition.y) * freeCameraComponent.m_sensetivity;
            }
        }
    }

private:
    glm::vec2 m_lastMousePosition;
};

int main(int argc, char** argv)
{
    Emerald::Game game{};
    entt::entity mainCamera = game.createEntity();
    game.addComponent<Emerald::Gfx::Camera>(mainCamera, 45.0f, 0.1f, 100);
    game.addComponent<FlyCameraComponent>(mainCamera, 1.0f, 0.1f);
    game.addSystem<FlyCameraSystem>();
    game.run();

    return 0;
}
