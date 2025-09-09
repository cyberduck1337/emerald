#pragma once

#include <tuple>

namespace Emerald
{
    template<typename T, typename... Ts>
    struct Subsystem
    {
        using Implementation = T;
        using Args = std::tuple<Ts...>;
    };
}

