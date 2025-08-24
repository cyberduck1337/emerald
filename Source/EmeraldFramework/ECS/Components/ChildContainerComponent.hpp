#pragma once

#include "ECS/Entity.hpp"
#include <vector>

namespace Emerald::ECS
{
    class ChildContainerComponent
    {
    public:
        std::vector<Entity> m_chilren;
    };
}
