#pragma  once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "Components/Transform.hpp"
#include "glm/fwd.hpp"

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
        using ElementBufferObjectType = uint32_t;
        using Texture2dObjectType = uint32_t;

        struct Vertex
        {
            glm::vec3 position;
            glm::vec2 uv;
        };

        using Triangle = std::array<uint32_t, 3>;

        class Mesh
        {
        public:
            Mesh(const std::vector<Vertex>& vertices, const std::vector<std::array<uint32_t, 3>>& triangles);
            Mesh(std::vector<Vertex>&& vertices, std::vector<std::array<uint32_t, 3>>&& triangles);
            ~Mesh();

        protected:
            std::vector<Vertex> m_vertices;
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

        class Texture2d final
        {
        public:
            Texture2d(uint32_t width, uint32_t height, uint32_t channels, Texture2dObjectType id) noexcept;
            
            [[nodiscard]]
            uint32_t width() const noexcept;

            [[nodiscard]]
            uint32_t height() const noexcept;

            [[nodiscard]]
            uint32_t channels() const noexcept;

            [[nodiscard]]
            Texture2dObjectType id() const noexcept;

        private:
            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_channels;
            Texture2dObjectType m_textureId;
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
        static void setShaderMat4x4Value(ShaderType shaderProgram, const std::string& name, const glm::mat4& value);
        static void destroyShader(ShaderType shader);
        static VertexBufferObjectType createVertexBufferObject();
        static void destroyVertexBufferObject(VertexBufferObjectType vertexBufferObject);
        static VertexArrayObjectType createVertexArrayObject();
        static void destroyVertexArrayObject(VertexArrayObjectType vertexArrayObject);
        static ElementBufferObjectType createElementBufferObject();
        static void destroyElementBufferObject(ElementBufferObjectType elementBufferObject);
        static Texture2dObjectType createTexture2dObject();
        static void destroyTexture2dObject(Texture2dObjectType texture2dObject);
        static void upload(VertexBufferObjectType vertexBufferObject, const std::vector<Vertex>& vertices, ElementBufferObjectType elementBufferObject, const std::vector<Triangle>& triangles);
        static void upload(Texture2dObjectType texture2dObject, const uint32_t width, const uint32_t height, const std::vector<uint8_t>& data);
        static void drawIndexedGeometry(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, size_t indexCount, ShaderType shaderProgram, VertexBufferObjectType vertexBufferObject, VertexArrayObjectType vertexArrayObject, ElementBufferObjectType elementBufferObject);
        static void swap();
        static void endFrame();
        static void destroy();

    private:
        static inline WindowType g_window { nullptr }; 
        static inline float g_deltaTime {};
        static inline ShaderType g_fallbackShader {};
    };
}
