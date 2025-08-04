#include "Gfx.hpp"
#include "Log.hpp"
#include <cstdint>

int main(int argc, char** argv)
{
    constexpr auto APPLICATION_NAME = "Emerald";
    
    constexpr uint32_t APPLICATION_DEFAULT_WINDOW_WIDHT = 1280;
    constexpr uint32_t APPLICATION_DEFAULT_WINDOW_HEIGHT = 720;

    Emerald::Log::initialize();
    Emerald::Gfx::initialize(APPLICATION_NAME, APPLICATION_DEFAULT_WINDOW_WIDHT, APPLICATION_DEFAULT_WINDOW_HEIGHT);

    Emerald::Gfx::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!Emerald::Gfx::windowShouldClose())
    {
        Emerald::Gfx::beginFrame();
        Emerald::Gfx::endFrame();
    }

    Emerald::Gfx::destroy();
    Emerald::Log::destroy();
    
    return 0;
}
