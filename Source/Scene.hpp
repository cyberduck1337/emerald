#pragma once

#include "Systems/SystemBase.hpp"
#include "Entity.hpp"
#include <memory>
#include <vector>

namespace Emerald
{
    class Scene final
    {
        friend class EntityUtils;

    public:
        Scene();
        ~Scene();

        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene&& operator=(Scene&&) = delete;

        static Scene& get();

        void update();

        [[nodiscard]]
        Entity getCameraObject() const noexcept;

        template<typename T, typename... Args>
        void addSystem(Args&&... args)
        {
            std::unique_ptr<T> system = std::make_unique<T>(std::forward<Args>(args)...);
            m_systems.emplace_back(std::move(system));
        }

        template<typename... Ts>
        decltype(auto) view() const
        {
            return m_registry.view<Ts...>();
        }

    private:
        static inline Scene* g_instance { nullptr };

        entt::registry m_registry;
        Entity m_camera;
        std::vector<std::unique_ptr<SystemBase>> m_systems;
    };
} // namespace Emerald
