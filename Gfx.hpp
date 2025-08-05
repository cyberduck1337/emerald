#pragma  once

#include <cstdint>
#include <string>
#include <cstdint>
#include <string_view>

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

        using ShaderType = uint32_t;

        enum class ShaderKind : uint32_t
        {
            VERTEX,
            FRAGMENT
        };

        static void initialize(const std::string& title, uint32_t width, uint32_t height);
        static void beginFrame();
        static bool windowShouldClose();
        static void setClearColor(float r, float g, float b, float a);
        static void clearBackgroud();
        static float deltaTime();
        static ShaderType compileShader(std::string_view source, ShaderKind kind);
        static ShaderType linkShaderProgram(ShaderType vertex, ShaderType fragment);
        static void swap();
        static void endFrame();
        static void destroy();

    private:
        static inline WindowType g_window { nullptr }; 
        static inline float g_deltaTime {};
    };
}
