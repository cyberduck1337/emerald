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

    Emerald::Transform mainCameraInitialTransform{};
    mainCameraInitialTransform.m_position = {0.0f, 0.0f, -2.5f};
    mainCameraInitialTransform.m_rotation = glm::quat(glm::radians(glm::vec3(90.0f, 0.0f, 0.0f)));
    Emerald::Entity mainCamera = Emerald::Entity::instantiate("MainCamera", mainCameraInitialTransform);
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
