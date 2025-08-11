#include "NameComponent.hpp"
#include <string>

namespace Emerald::ECS
{
    NameComponent::NameComponent(const std::string& name) : m_name(name)
    {
    }

    void NameComponent::setName(const std::string& name)
    {
        m_name = name;
    }

    const std::string& NameComponent::getName() const
    {
        return m_name;
    }
}
