#pragma once

namespace Emerald
{
    class Reflection
    {
    public:
        Reflection() = delete;
        ~Reflection() = delete;

        static void initialize();
        static void destroy();
    };
} // namespace Emerald
