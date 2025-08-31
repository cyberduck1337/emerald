#pragma once

#include <string>

namespace Emerald
{
    class NameComponent final
    {
    public:
        explicit NameComponent(const std::string& name);

        [[nodiscard]]
        const std::string& getName() const;

        void setName(const std::string& name);

    private:
        std::string m_name;
    };
} // namespace Emerald
