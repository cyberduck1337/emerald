#include "SceneGraph.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Components/ChildContainerComponent.hpp"

namespace Emerald
{
    SceneGraph::SceneGraph() : m_registry(), m_root(m_registry.create())
    {
        m_registry.emplace<ECS::Transform>(m_root);
        m_registry.emplace<ECS::ChildContainerComponent>(m_root);
    }
}
