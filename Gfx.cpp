#include "Gfx.hpp"
#include "glad/glad.h"
#include "Assertion.hpp"
#include "GLFW/glfw3.h"
#include "fmt/format.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <cstdint>
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
        static float g_lastFrameTime {};

        float currentTime = glfwGetTime();
        g_deltaTime = currentTime - g_lastFrameTime;
        g_lastFrameTime = currentTime;
        
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

    float Gfx::deltaTime()
    {
        return g_deltaTime;
    }

    Gfx::ShaderType Gfx::compileShader(std::string_view source, ShaderKind kind)
    {
        Gfx::ShaderType shader {};

        switch (kind)
        {
            case Gfx::ShaderKind::VERTEX:
                shader = glCreateShader(GL_VERTEX_SHADER);
                break;
            case Gfx::ShaderKind::FRAGMENT:
                shader = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            default:
                EMERALD_VERIFY_THROW(false, std::runtime_error, fmt::format("Unexpected ShaderKind {:#x}", static_cast<uint32_t>(kind)));
        }

        int32_t success;
        char info[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, std::size(info), nullptr, info);
            EMERALD_VERIFY_THROW(false, std::runtime_error, fmt::format("Failed to compile shader: {}", info));
        }

        return shader;
    }

    Gfx::ShaderType Gfx::linkShaderProgram(ShaderType vertex, ShaderType fragment)
    {
        Gfx::ShaderType shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertex);
        glAttachShader(shaderProgram, fragment);
        glLinkProgram(shaderProgram);

        int32_t success;
        char info[512];
        glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shaderProgram, std::size(info), nullptr, info);
            EMERALD_VERIFY_THROW(false, std::runtime_error, fmt::format("Failed to link shader: {}", shaderProgram));
        }

        return shaderProgram;
    }

    void Gfx::destroyShader(ShaderType shader)
    {
        glDeleteShader(shader);
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
