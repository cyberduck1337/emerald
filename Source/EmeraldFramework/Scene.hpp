#pragma once

#include "ECS/Systems/SystemBase.hpp"
#include "SceneGraph.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Components/Transform.hpp"
#include <vector>

namespace Emerald
{
    class Scene final : public SceneGraph
    {
    public:
        Scene(const std::string& name);

    private:
        ECS::Entity addEntity(const std::string& name, ECS::Transform transform, ECS::Entity parent);
        void update();

    private:
        std::string m_name;
        std::vector<std::unique_ptr<ECS::SystemBase>> m_systems;
    };
}
