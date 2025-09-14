#include "Gfx.hpp"
#include <cstdint>
#include <stdexcept>
#include "Assertion.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Log.hpp"
#include "fmt/format.h"
#include "glm/gtc/type_ptr.hpp"

#define GL_COMMAND(command, ...)                                          \
    command(__VA_ARGS__);                                                 \
    {                                                                     \
        GLenum errorCode{};                                               \
        while ((errorCode = glGetError()) != GL_NO_ERROR)                 \
        {                                                                 \
            std::string error{};                                          \
            switch (errorCode)                                            \
            {                                                             \
                case GL_INVALID_ENUM:                                     \
                    error = "GL_INVALID_ENUM";                            \
                    break;                                                \
                case GL_INVALID_VALUE:                                    \
                    error = "GL_INVALID_VALUE";                           \
                    break;                                                \
                case GL_INVALID_OPERATION:                                \
                    error = "GL_INVALID_OPERATION";                       \
                    break;                                                \
                case GL_STACK_OVERFLOW:                                   \
                    error = "GL_STACK_OVERFLOW";                          \
                    break;                                                \
                case GL_STACK_UNDERFLOW:                                  \
                    error = "GL_STACK_UNDERFLOW";                         \
                    break;                                                \
                case GL_OUT_OF_MEMORY:                                    \
                    error = "GL_OUT_OF_MEMORY";                           \
                    break;                                                \
                case GL_INVALID_FRAMEBUFFER_OPERATION:                    \
                    error = "GL_INVALID_FRAMEBUFFER_OPERATION";           \
                    break;                                                \
                default:                                                  \
                    error = "GL_ERROR_UNKNOWN";                           \
                    break;                                                \
            }                                                             \
            Emerald::Log::error("{} | {}:{}", error, __FILE__, __LINE__); \
        }                                                                 \
    }

namespace
{
    void glfwWindowResizeCallback(WindowType window, const int width, const int height)
    {
        GL_COMMAND(glViewport, 0, 0, width, height);
    }
}

namespace Emerald
{
    constexpr auto SOLID_COLOR_VERTEX_SHADER = R"(
        #version 460 core

        layout (location = 0) in vec3 inPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(inPos, 1.0);
        }
    )";

    constexpr auto SOLID_COLOR_FRAGMENT_SHADER = R"(
        #version 460 core

        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.5, 0.2, 0.3, 1.0);
        }
    )";

    Gfx::Mesh::Mesh(const std::vector<Gfx::Vertex>& vertices, const std::vector<std::array<uint32_t, 3>>& triangles) : m_vertices(vertices), m_triangles(triangles), m_vertexBufferObject(createVertexBufferObject()), m_vertexArrayObject(createVertexArrayObject())
    {
    }

    Gfx::Mesh::Mesh(std::vector<Gfx::Vertex>&& vertices, std::vector<std::array<uint32_t, 3>>&& triangles) :  m_vertices(std::move(vertices)), m_triangles(std::move(triangles)), m_vertexBufferObject(createVertexBufferObject()), m_vertexArrayObject(createVertexArrayObject())
    {
    }

    Gfx::Mesh::~Mesh()
    {
        destroyVertexArrayObject(m_vertexArrayObject);
        destroyVertexBufferObject(m_vertexBufferObject);

        m_vertices.clear();
        m_triangles.clear();
    }

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

        GL_COMMAND(glViewport, 0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
        glfwSetFramebufferSizeCallback(g_window, glfwWindowResizeCallback);

        GL_COMMAND(glFrontFace, GL_CCW);
        GL_COMMAND(glEnable, GL_CULL_FACE);

        const ShaderType fallbackVertexShader = compileShader(SOLID_COLOR_VERTEX_SHADER, ShaderKind::VERTEX);
        const ShaderType fallbackFragmentShader = compileShader(SOLID_COLOR_FRAGMENT_SHADER, ShaderKind::FRAGMENT);
        g_fallbackShader = linkShaderProgram(fallbackVertexShader, fallbackFragmentShader);
        destroyShader(fallbackVertexShader);
        destroyShader(fallbackFragmentShader);
    }

    void Gfx::beginFrame()
    {
        static float g_lastFrameTime {};

        const float currentTime = static_cast<float>(glfwGetTime());
        g_deltaTime = currentTime - g_lastFrameTime;
        g_lastFrameTime = currentTime;

        glfwPollEvents();
        clearBackground();
    }

    bool Gfx::windowShouldClose()
    {
        return glfwWindowShouldClose(g_window);
    }

    glm::uvec2 Gfx::getWindowSize()
    {
        int32_t w{};
        int32_t h{};
        glfwGetWindowSize(g_window, &w, &h);

        return {w, h};
    }

    void Gfx::setClearColor(float r, float g, float b, float a)
    {
        GL_COMMAND(glClearColor, r, g, b, a);
    }

    void Gfx::clearBackground()
    {
        GL_COMMAND(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    float Gfx::deltaTime()
    {
        return g_deltaTime;
    }

    Gfx::ShaderType Gfx::compileShader(std::string_view source, ShaderKind kind)
    {
        ShaderType shader {};

        switch (kind)
        {
            case ShaderKind::VERTEX:
            {
                shader = GL_COMMAND(glCreateShader, GL_VERTEX_SHADER);
                break;
            }
            case ShaderKind::FRAGMENT:
            {
                shader = GL_COMMAND(glCreateShader, GL_FRAGMENT_SHADER);
                break;
            }
            default:
                EMERALD_VERIFY_THROW(false, std::runtime_error, fmt::format("Unexpected ShaderKind {:#x}", static_cast<uint32_t>(kind)));
        }
        
        const char* shaderSourcePtr = source.data();
        GL_COMMAND(glShaderSource, shader, 1, &shaderSourcePtr, nullptr);
        GL_COMMAND(glCompileShader, shader);

        int32_t success;
        char info[512];
        GL_COMMAND(glGetShaderiv, shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            GL_COMMAND(glGetShaderInfoLog, shader,  std::size(info), nullptr, info);
            EMERALD_VERIFY_THROW(false, std::runtime_error, fmt::format("Failed to compile shader: {}", info));
        }

        return shader;
    }

    Gfx::ShaderType Gfx::linkShaderProgram(ShaderType vertex, ShaderType fragment)
    {
        ShaderType shaderProgram = GL_COMMAND(glCreateProgram);

        GL_COMMAND(glAttachShader, shaderProgram, vertex);
        GL_COMMAND(glAttachShader, shaderProgram, fragment);
        GL_COMMAND(glLinkProgram, shaderProgram);

        int32_t success;
        char info[512];
        GL_COMMAND(glGetProgramiv, shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            GL_COMMAND(glGetProgramInfoLog, shaderProgram, std::size(info), nullptr, info);
            EMERALD_VERIFY_THROW(false, std::runtime_error, fmt::format("Failed to link shader: {}", shaderProgram));
        }

        return shaderProgram;
    }

    Gfx::ShaderType Gfx::fallbackShader()
    {
        return g_fallbackShader;       
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, bool value)
    {
        const int32_t uniformLocation = GL_COMMAND(glGetUniformLocation, shaderProgram, name.c_str());
        GL_COMMAND(glUniform1i, uniformLocation, static_cast<GLint>(value));
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, int32_t value)
    {
        const int32_t uniformLocation = GL_COMMAND(glGetUniformLocation, shaderProgram, name.c_str());
        GL_COMMAND(glUniform1i, uniformLocation, value);
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, float value)
    {
        const int32_t uniformLocation = GL_COMMAND(glGetUniformLocation, shaderProgram, name.c_str());
        GL_COMMAND(glUniform1f, uniformLocation, value);

    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, const glm::mat4& value)
    {
        const int32_t uniformLocation = GL_COMMAND(glGetUniformLocation, shaderProgram, name.c_str());
        GL_COMMAND(glUniformMatrix4fv, uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Gfx::setShaderMat4x4Value(ShaderType shaderProgram, const std::string& name, const glm::mat4& value)
    {
        const int32_t uniformLocation = GL_COMMAND(glGetUniformLocation, shaderProgram, name.c_str());
        GL_COMMAND(glUniformMatrix4fv, uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Gfx::destroyShader(ShaderType shader)
    {
        GL_COMMAND(glDeleteShader, shader);
    }

    Gfx::VertexBufferObjectType Gfx::createVertexBufferObject()
    {
        VertexBufferObjectType vertexBufferObject{};
        GL_COMMAND(glGenBuffers, 1, &vertexBufferObject);

        return vertexBufferObject;
    }

    void Gfx::destroyVertexBufferObject(VertexBufferObjectType vertexBufferObject)
    {
        GL_COMMAND(glDeleteBuffers, 1, &vertexBufferObject);
    }

    Gfx::VertexArrayObjectType Gfx::createVertexArrayObject()
    {
        VertexArrayObjectType vertexArrayObject{};
        GL_COMMAND(glGenVertexArrays, 1, &vertexArrayObject);

        return vertexArrayObject;
    }

    void Gfx::destroyVertexArrayObject(VertexArrayObjectType vertexArrayObject)
    {
        GL_COMMAND(glDeleteVertexArrays, 1, &vertexArrayObject);
    }

    Gfx::ElementBufferObjectType Gfx::createElementBufferObject()
    {
        ElementBufferObjectType elementBufferObject{};
        GL_COMMAND(glGenBuffers, 1, &elementBufferObject);

        return elementBufferObject;
    }

    void Gfx::destroyElementBufferObject(ElementBufferObjectType elementBufferObject)
    {
        GL_COMMAND(glDeleteVertexArrays, 1, &elementBufferObject);
    }

    void Gfx::upload(VertexBufferObjectType vertexBufferObject, const std::vector<Vertex>& vertices, ElementBufferObjectType elementBufferObject, const std::vector<Triangle>& triangles)
    {
        GL_COMMAND(glBindBuffer, GL_ARRAY_BUFFER, vertexBufferObject);
        GL_COMMAND(glBufferData, GL_ARRAY_BUFFER, sizeof(std::vector<Vertex>::value_type) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        GL_COMMAND(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
        GL_COMMAND(glBufferData, GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(std::vector<Triangle>::value_type), triangles.data(), GL_STATIC_DRAW);
    }

    void Gfx::drawIndexedGeometry(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, size_t indexCount, ShaderType shaderProgram, VertexBufferObjectType vertexBufferObject, VertexArrayObjectType vertexArrayObject, ElementBufferObjectType elementBufferObject)
    {
        GL_COMMAND(glBindVertexArray, vertexArrayObject);

        GL_COMMAND(glBindBuffer, GL_ARRAY_BUFFER, vertexBufferObject);
        GL_COMMAND(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

        GL_COMMAND(glEnableVertexAttribArray, 0);
        GL_COMMAND(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

        GL_COMMAND(glEnableVertexAttribArray, 1);
        GL_COMMAND(glVertexAttribPointer, 1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

        GL_COMMAND(glUseProgram, shaderProgram);

        setShaderMat4x4Value(shaderProgram, "model", model);
        setShaderMat4x4Value(shaderProgram, "view", view);
        setShaderMat4x4Value(shaderProgram, "projection", projection);

        GL_COMMAND(glDrawElements, GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Gfx::swap()
    {
        glfwSwapBuffers(g_window);
    }

    void Gfx::endFrame()
    {
        swap();
    }

    void Gfx::destroy()
    {
        glfwDestroyWindow(g_window);
        glfwTerminate();
    }
}
