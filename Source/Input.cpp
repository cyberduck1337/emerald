#include "Input.hpp"
#include "GLFW/glfw3.h"
#include "Gfx.hpp"

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

    bool Input::getMouseButton(MouseButton button)
    {
        return static_cast<bool>(glfwGetMouseButton(Gfx::g_window, static_cast<int>(button)));
    }

    bool Input::getMouseButtonDown(MouseButton button)
    {
        return glfwGetMouseButton(Gfx::g_window, static_cast<int>(button)) == GLFW_PRESS;
    }

    bool Input::getMouseButtonUp(MouseButton button)
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
