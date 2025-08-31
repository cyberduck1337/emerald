#pragma  once

#include <array>
#include <cstdint>
#include <string>
#include <cstdint>
#include <string_view>
#include <vector>

#include "Input.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_uint2.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/quaternion.hpp"

using WindowType = struct GLFWwindow*;

namespace Emerald
{
    class Gfx final
    {
        friend class Input;

    public:
        Gfx() = delete;
        ~Gfx() = delete;

        using ShaderType = uint32_t;
        using VertexBufferObjectType = uint32_t;
        using VertexArrayObjectType = uint32_t;

        struct Vertex
        {
            glm::vec3 position;
            glm::vec2 uv;
        };

        class Mesh
        {
        public:
            Mesh(const std::vector<Gfx::Vertex>& vertices, const std::vector<std::array<uint32_t, 3>>& triangles);
            Mesh(std::vector<Gfx::Vertex>&& vertices, std::vector<std::array<uint32_t, 3>>&& triangles);
            ~Mesh();

        protected:
            std::vector<Gfx::Vertex> m_vertices;
            std::vector<std::array<uint32_t, 3>> m_triangles;

            VertexBufferObjectType m_vertexBufferObject;
            VertexArrayObjectType m_vertexArrayObject;
        };

        enum class ShaderKind : uint32_t
        {
            VERTEX,
            FRAGMENT
        };

        struct Attribute
        {
            enum class Type : uint32_t
            {
                BYTE,
                UNSIGNED_BYTE,
                SHORT,
                UNSIGNED_SHORT,
                INTEGER,
                UNSIGNED_INTEGER,
                FLOAT
            };

            uint32_t index;
            uint32_t numComponents;
            size_t stride;
            Type type;
            uintptr_t offset;
            bool aligned;
        };

        static void initialize(const std::string& title, uint32_t width, uint32_t height);
        static void beginFrame();
        static bool windowShouldClose();
        static glm::uvec2 getWindowSize();
        static void setClearColor(float r, float g, float b, float a);
        static void clearBackground();
        static float deltaTime();
        static ShaderType compileShader(std::string_view source, ShaderKind kind);
        static ShaderType linkShaderProgram(ShaderType vertex, ShaderType fragment);
        static ShaderType fallbackShader();
        static void setShaderUniformValue(ShaderType shaderProgram, const std::string& name, bool value);
        static void setShaderUniformValue(ShaderType shaderProgram, const std::string& name, int32_t value);
        static void setShaderUniformValue(ShaderType shaderProgram, const std::string& name, float value);
        static void setShaderUniformValue(ShaderType shaderProgram, const std::string& name, const glm::mat4& value);
        static void destroyShader(ShaderType shader);
        static VertexBufferObjectType createVertexBufferObject();
        static void destroyVertexBufferObject(VertexBufferObjectType vertexBufferObject);
        static VertexArrayObjectType createVertexArrayObject();
        static void destroyVertexArrayObject(VertexArrayObjectType vertexArrayObject);
        static void swap();
        static void endFrame();
        static void destroy();

    private:
        static inline WindowType g_window { nullptr }; 
        static inline float g_deltaTime {};
        static inline ShaderType g_fallbackShader {};
    };
}
