#pragma once

#include "ECS/Entity.hpp"

namespace Emerald
{
    class SceneGraph
    {
    protected:
        SceneGraph();

    protected:
        entt::registry m_registry;
        entt::entity m_root;
    };
}
