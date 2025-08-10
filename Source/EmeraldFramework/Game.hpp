#pragma once

#include <type_traits>
#include <utility>
#include <vector>
#include "System.hpp"
#include "entt/entity/fwd.hpp"

namespace Emerald
{
    class Game final
    {
    public:
        Game(Game& other) = delete;
        Game(Game&& other) = delete;
        void operator=(Game& other) = delete;
        void operator=(Game&& other) = delete;

        Game();
        ~Game();

        void run();

        entt::entity createEntity();
        void update();

        static Game& get();

        template<typename T, typename... Args>
        void addComponent(entt::entity entity, Args&&... args)
        {
            m_registry.emplace<T>(entity, std::forward<Args>(args)...);
        }

        template<typename T, typename... Args>
        void addSystem(Args&&... args) requires std::is_base_of_v<Emerald::ECS::System, T>
        {
            m_systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        }

    private:
        static inline Game* g_instance = nullptr;
        entt::registry m_registry;
        std::vector<std::unique_ptr<Emerald::ECS::System>> m_systems;
    };
}