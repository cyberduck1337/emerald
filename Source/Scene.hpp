#pragma once

#include <vector>
#include "Systems/SystemBase.hpp"

namespace Emerald
{
    class Scene final
    {
    public:
        explicit Scene(std::string name);
        ~Scene();

        void update();

        template<typename T, typename... Args>
        void addSystem(Args&&... args)
        {
            std::unique_ptr<T> system = std::make_unique<T>(std::move<Args>(args)...);
            m_systems.emplace_back(std::move(system));
        }

    private:
        std::string m_name;
        std::vector<std::unique_ptr<SystemBase>> m_systems;
    };
} // namespace Emerald
