#include "Input.hpp"
#include "Gfx.hpp"
#include "GLFW/glfw3.h"

namespace Emerald
{
    bool Input::getKey(KeyCode keyCode)
    {
        return static_cast<bool>(glfwGetKey(Gfx::g_window, static_cast<int>(keyCode)));
    }

    bool Input::getKeyDown(KeyCode keyCode)
    {
        return glfwGetKey(Gfx::g_window, static_cast<int>(keyCode)) == GLFW_PRESS;
    }

    bool Input::getKeyUp(KeyCode keyCode)
    {
        return glfwGetKey(Gfx::g_window, static_cast<int>(keyCode)) == GLFW_RELEASE;
    }

    bool Input::getMouseButton(uint32_t button)
    {
        return static_cast<bool>(glfwGetMouseButton(Gfx::g_window, static_cast<int>(button)));
    }

    bool Input::getMouseButtonDown(uint32_t button)
    {
        return glfwGetMouseButton(Gfx::g_window, static_cast<int>(button)) == GLFW_PRESS;
    }

    bool Input::getMouseButtonUp(uint32_t button)
    {
        return glfwGetMouseButton(Gfx::g_window, static_cast<int>(button)) == GLFW_RELEASE;
    }

    glm::vec2 Input::getMousePosition()
    {
        double x; 
        double y;
        glfwGetCursorPos(Gfx::g_window, &x, &y);

        return { static_cast<float>(x), static_cast<float>(y)};
    }
}
