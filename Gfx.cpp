#include "Gfx.hpp"
#include "glad/glad.h"
#include "Assertion.hpp"
#include "GLFW/glfw3.h"
#include "fmt/format.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_uint2.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/gl.h>
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
    constexpr auto SOLID_COLOR_VERTEX_SHADER = R"(
        #version 460 core

        layout (location = 0) in vec3 inPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec4 outPos;

        void main()
        {
            outPos = projection * view * model * vec4(inPos, 1.0);
        }
    )";

    constexpr auto SOLID_COLOR_FRAGMENT_SHADER = R"(
        #version 460 core

        layout (location = 0) in vec3 inColor;

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(inColor, 1.0);
        }
    )";

    glm::vec3 Gfx::Transform::eulerAngles() const
    {
        return glm::degrees(glm::eulerAngles(glm::normalize(rotation)));
    }

    glm::vec3 Gfx::Transform::direction() const
    {
        const glm::vec3 rot = eulerAngles();

        return {
            glm::cos(glm::radians(rot.x)) * glm::cos(glm::radians(rot.y)),
            glm::sin(glm::radians(rot.y)),
            glm::sin(glm::radians(rot.x)) * glm::cos(glm::radians(rot.y))
        };
    }

    glm::vec3 Gfx::Transform::front() const
    {
        return glm::normalize(direction());
    }

    glm::vec3 Gfx::Transform::right() const
    {
        return glm::normalize(glm::cross(VECTOR_UP, front()));
    }

    glm::vec3 Gfx::Transform::up() const
    {
        return glm::normalize(glm::cross(right(), front()));
    }

    void Gfx::Transform::rotate(const glm::vec3& eulerAngles)
    {
        glm::quat eulerRot = glm::quat(glm::radians(eulerAngles));
        rotation *= glm::inverse(rotation) * eulerRot * rotation;
    }

    glm::mat4 Gfx::Transform::model() const
    {
        return (glm::translate(position) * glm::toMat4(rotation) * glm::scale(scale));
    }

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

    Gfx::Camera::Camera(float fov, float near, float far) : m_fov(fov), m_near(near), m_far(far)
    {
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

        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(g_window, glfwWindowRezieCallback);

        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);

        ShaderType fallbackVertexShader = compileShader(SOLID_COLOR_VERTEX_SHADER, ShaderKind::VERTEX);
        ShaderType fallbackFragmentShader = compileShader(SOLID_COLOR_FRAGMENT_SHADER, ShaderKind::FRAGMENT);
        g_fallbackShader = linkShaderProgram(fallbackVertexShader, fallbackFragmentShader);
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

    glm::uvec2 Gfx::getWindowSize()
    {
        int32_t w{};
        int32_t h{};
        glfwGetWindowSize(g_window, &w, &h);

        return {w, h};
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
        
        const char* shaderSourcePtr = source.data();
        glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
        glCompileShader(shader);

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

    Gfx::ShaderType Gfx::fallbackShader()
    {
        return g_fallbackShader;       
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, bool value)
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), static_cast<uint32_t>(value));
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, int32_t value)
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void Gfx::setShaderUniformValue(ShaderType shaderProgram, const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Gfx::destroyShader(ShaderType shader)
    {
        glDeleteShader(shader);
    }

    Gfx::VertexBufferObjectType Gfx::createVertexBufferObject()
    {
        Gfx::VertexBufferObjectType vertexBufferObject{};
        glGenBuffers(1, &vertexBufferObject);

        return vertexBufferObject;
    }

    void Gfx::destroyVertexBufferObject(VertexBufferObjectType vertexBufferObject)
    {
        glDeleteBuffers(1, &vertexBufferObject);
    }

    Gfx::VertexArrayObjectType Gfx::createVertexArrayObject()
    {
        Gfx::VertexArrayObjectType vertexArrayObject{};
        glGenVertexArrays(1, &vertexArrayObject);

        return vertexArrayObject;
    }

    void Gfx::destroyVertexArrayObject(VertexArrayObjectType vertexArrayObject)
    {
        glDeleteVertexArrays(1, &vertexArrayObject);
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
