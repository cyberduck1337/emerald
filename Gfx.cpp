#include "Gfx.hpp"
#include "glad/glad.h"
#include "Assertion.hpp"
#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <stdexcept>

namespace
{
    void glfwWindowRezieCallback(WindowType window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}

namespace Emerald
{
    void Gfx::initialize(const std::string& title, uint32_t width, uint32_t height)
    {
        EMERALD_VERIFY_THROW(glfwInit() == GLFW_TRUE, std::runtime_error, "Failed to inistalize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        g_window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
        EMERALD_VERIFY_THROW(g_window != nullptr, std::runtime_error, "Failed to initialize GLFW window");

        glfwMakeContextCurrent(g_window);
        
        EMERALD_VERIFY_THROW(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), std::runtime_error, "Failed to initialize glad");

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(g_window, glfwWindowRezieCallback);

        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
    }

    void Gfx::beginFrame()
    {
        clearBackgroud();
    }

    bool Gfx::windowShouldClose()
    {
        return glfwWindowShouldClose(g_window);
    }

    void Gfx::setClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Gfx::clearBackgroud()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Gfx::swap()
    {
        glfwSwapBuffers(g_window);
    }

    void Gfx::endFrame()
    {
        glfwPollEvents();
        swap();
    }

    void Gfx::destroy()
    {
        glfwDestroyWindow(g_window);
        glfwTerminate();
    }
}
