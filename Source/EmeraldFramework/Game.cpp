#include "Game.hpp"
#include "Gfx.hpp"
#include "Assertion.hpp"
#include "Log.hpp"
#include "entt/entity/fwd.hpp"
#include <stdexcept>

namespace Emerald
{
    Game::Game()
    {
        EMERALD_VERIFY_THROW(g_instance == nullptr, std::runtime_error, "Game instance already exist!");
        g_instance = this;

        constexpr auto APPLICATION_NAME = "Emerald";

        constexpr uint32_t APPLICATION_DEFAULT_WINDOW_WIDHT = 1280;
        constexpr uint32_t APPLICATION_DEFAULT_WINDOW_HEIGHT = 720;

        Emerald::Log::initialize();
        Emerald::Gfx::initialize(APPLICATION_NAME, APPLICATION_DEFAULT_WINDOW_WIDHT, APPLICATION_DEFAULT_WINDOW_HEIGHT);
    }

    Game::~Game()
    {
        Emerald::Gfx::destroy();
        Emerald::Log::destroy();
    }

    void Game::run()
    {
        Emerald::Gfx::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        while (!Emerald::Gfx::windowShouldClose())
        {
            Emerald::Gfx::beginFrame();
            update();
            Emerald::Gfx::endFrame();
        }
    }

    entt::entity Game::createEntity()
    {
        entt::entity entity = m_registry.create();
        m_registry.emplace<Gfx::Transform>(entity);
        return entity;
    }

    void Game::update()
    {
        for(auto&& system : m_systems)
        {
            system->update(m_registry);
        }

        auto cameraComponentView = m_registry.view<const Gfx::Transform, Gfx::Camera>();
        for(auto&& [entity, transform, camera] : cameraComponentView.each())
        {
            const glm::uvec2 windowSize = Gfx::getWindowSize();

            camera.m_projection = glm::perspective(glm::radians(camera.m_fov), static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y), camera.m_near, camera.m_far);
            camera.m_view = glm::lookAt(transform.position, transform.position + transform.front(), transform.up());
        }
    }

    Game& Game::get()
    {
        EMERALD_VERIFY_THROW(g_instance != nullptr, std::runtime_error, "Game has not been initialized yet!");
        return *g_instance;
    }
}
