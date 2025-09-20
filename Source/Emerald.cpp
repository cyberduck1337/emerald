#include "Components/CameraComponent.hpp"
#include "Components/FreeCameraComponent.hpp"
#include "Components/StaticMeshComponent.hpp"
#include "Components/Transform.hpp"
#include "Gfx.hpp"
#include "Log.hpp"
#include "Reflection.hpp"
#include "Scene.hpp"
#include "Systems/FreeCameraControlSystem.hpp"

int main(int argc, char** argv)
{
    Emerald::Log::initialize();
    Emerald::Reflection::initialize();
    Emerald::Gfx::initialize("Emerald", 1280, 720);
    Emerald::Gfx::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    {
        Emerald::Log::info("Welcome to Emerald!");
        Emerald::Scene world{};

        Emerald::EntityUtils::addComponent<Emerald::FreeCameraComponent>(world.getCameraObject(), 2.0f, 0.5f);
        world.addSystem<Emerald::FreeCameraControlSystem>();

        const Emerald::Entity cube1 = Emerald::EntityUtils::instantiate("cube1", {0.0f, 0.0f, 0.0f});
        std::vector<Emerald::Gfx::Vertex> m_vertices = {
            /*[ 0]*/ {{-0.5f, -0.5f,  0.5f},     {0.0f, 1.0f / 3}},  // front  - bottom - left
            /*[ 1]*/ {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f / 3 * 2}},  // front  - top    - left
            /*[ 2]*/ {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f / 3 * 2}},  // front  - top    - right
            /*[ 3]*/ {{ 0.5f, -0.5f,  0.5f},     {1.0f, 1.0f / 3}},  // front  - bottom - right
            /*[ 4]*/ {{-0.5f, -0.5f, -0.5f},     {0.0f, 1.0f / 3}},  // back   - bottom - left
            /*[ 5]*/ {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f / 3 * 2}},  // back   - top    - left
            /*[ 6]*/ {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f / 3 * 2}},  // back   - top    - right
            /*[ 7]*/ {{ 0.5f, -0.5f, -0.5f},     {1.0f, 1.0f / 3}},  // back   - bottom - right
            /*[ 8]*/ {{-0.5f, -0.5f, -0.5f},     {0.0f, 1.0f / 3}},  // left   - bottom - back
            /*[ 9]*/ {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f / 3 * 2}},  // left   - top    - back
            /*[10]*/ {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f / 3 * 2}},  // left   - top    - front
            /*[11]*/ {{-0.5f, -0.5f,  0.5f},     {1.0f, 1.0f / 3}},  // left   - bottom - front
            /*[12]*/ {{ 0.5f, -0.5f, -0.5f},     {0.0f, 1.0f / 3}},  // right  - bottom - back
            /*[13]*/ {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f / 3 * 2}},  // right  - top    - back
            /*[14]*/ {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f / 3 * 2}},  // right  - top    - front
            /*[15]*/ {{ 0.5f, -0.5f,  0.5f},     {1.0f, 1.0f / 3}},  // right  - bottom - front
            /*[16]*/ {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f / 3 * 2}},  // top    - near   - left
            /*[17]*/ {{-0.5f,  0.5f, -0.5f},         {0.0f, 1.0f}},  // top    - far    - left
            /*[18]*/ {{ 0.5f,  0.5f, -0.5f},         {1.0f, 1.0f}},  // top    - far    - right
            /*[19]*/ {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f / 3 * 2}},  // top    - near   - right
            /*[20]*/ {{-0.5f, -0.5f,  0.5f},         {0.0f, 0.0f}},  // bottom - near   - left
            /*[21]*/ {{-0.5f, -0.5f, -0.5f},     {0.0f, 1.0f / 3}},  // bottom - far    - left
            /*[22]*/ {{ 0.5f, -0.5f, -0.5f},     {1.0f, 1.0f / 3}},  // bottom - far    - right
            /*[23]*/ {{ 0.5f, -0.5f,  0.5f},         {1.0f, 0.0f}},  // bottom - near   - right
        };

        std::vector<Emerald::Gfx::Triangle> m_triangles = {
            { 2,  1,  0},  {0,  3,  2}, // front
            { 7,  5,  6},  {7,  4,  5}, // back
            { 8, 11, 10},  {9,  8, 10}, // left
            {15, 12, 13}, {13, 14, 15}, // right
            {17, 16, 19}, {18, 17, 19}, // top
            {21, 22, 20}, {23, 20, 22}, // bottom
        };
        Emerald::EntityUtils::addComponent<Emerald::StaticMeshComponent>(cube1, m_vertices, m_triangles);

        while (!Emerald::Gfx::windowShouldClose())
        {
            Emerald::Gfx::beginFrame();

            world.update();

            auto view = world.view<const Emerald::Transform, const Emerald::StaticMeshComponent>();

            Emerald::Entity renderCamera = world.getCameraObject();
            const Emerald::Transform& renderCameraTransform = Emerald::EntityUtils::getComponent<Emerald::Transform>(renderCamera);
            Emerald::CameraComponent& renderCameraComponent = Emerald::EntityUtils::getComponent<Emerald::CameraComponent>(renderCamera);
            for (auto&&[entity, transform, staticMesh] : view.each())
            {
                Emerald::Gfx::ShaderType shaderProgram = Emerald::Gfx::fallbackShader();
                Emerald::Gfx::drawIndexedGeometry(transform.model(), renderCameraComponent.m_view, renderCameraComponent.m_projection, staticMesh.indicesCount(), shaderProgram, staticMesh.vbo(), staticMesh.vao(), staticMesh.ebo());
            }

            const glm::uvec2 windowSize = Emerald::Gfx::getWindowSize();

            renderCameraComponent.m_projection = glm::perspective(glm::radians(renderCameraComponent.m_fov), static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y), renderCameraComponent.m_near, renderCameraComponent.m_far);
            renderCameraComponent.m_view = glm::lookAt(renderCameraTransform.m_position, renderCameraTransform.m_position + renderCameraTransform.front(), renderCameraTransform.up());

            Emerald::Gfx::endFrame();
        }

        Emerald::Log::info("Goodbye, Emerald!");
    }

    Emerald::Gfx::destroy();
    Emerald::Reflection::destroy();
    Emerald::Log::destroy();

    return 0;
}
