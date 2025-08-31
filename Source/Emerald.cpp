#include "Gfx.hpp"
#include "Log.hpp"
#include "Scene.hpp"
#include "Systems/CameraUpdateSystem.hpp"

int main(int argc, char** argv)
{
    Emerald::Scene world{"World"};

    Emerald::Log::initialize();
    Emerald::Gfx::initialize("Emerald", 1280, 720);

    Emerald::Log::info("Welcome to Emerald!");

    world.addSystem<Emerald::CameraUpdateSystem>();

    Emerald::Transform mainCameraInitialTransform{}
    auto mainCamera = Emerald::Entity::instantiate("MainCamera");
    mainCamera.addComponent<Emerald::CameraComponent>(45.0f, 0.1f, 100.0f);

    while (!Emerald::Gfx::windowShouldClose())
    {
        Emerald::Gfx::beginFrame();
        world.update();
        Emerald::Gfx::endFrame();
    }

    Emerald::Log::info("Goodbye, Emerald!");

    Emerald::Gfx::destroy();
    Emerald::Log::destroy();

    return 0;
}
