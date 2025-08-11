#pragma once

#include <string>

namespace Emerald::ECS
{
    class NameComponent final
    {
    public:
        NameComponent(const std::string& name);

        void setName(const std::string& name);
        const std::string& getName() const;

    private:
        std::string m_name;
    };
}
