#pragma  once

#include <cstdint>
#include <string>
#include <cstdint>

namespace
{
    using WindowType = struct GLFWwindow*;
}

namespace Emerald
{
    class Gfx final
    {
    public:
        Gfx() = delete;
        ~Gfx() = delete;

        static void initialize(const std::string& title, uint32_t width, uint32_t height);
        static void beginFrame();
        static bool windowShouldClose();
        static void setClearColor(float r, float g, float b, float a);
        static void clearBackgroud();
        static float deltaTime();
        static void swap();
        static void endFrame();
        static void destroy();

    private:
        static inline WindowType g_window { nullptr }; 
        static inline float g_deltaTime {};
    };
}
