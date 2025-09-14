#pragma once

#include "Gfx.hpp"

namespace Emerald
{
    class StaticMeshComponent
    {
    public:
        StaticMeshComponent(const std::vector<Gfx::Vertex>& vertices, const std::vector<Gfx::Triangle>& triangles) noexcept;
        ~StaticMeshComponent() noexcept;

        [[nodiscard]]
        Gfx::VertexBufferObjectType vbo() const noexcept;

        [[nodiscard]]
        Gfx::VertexArrayObjectType vao() const noexcept;

        [[nodiscard]]
        Gfx::ElementBufferObjectType ebo() const noexcept;

        [[nodiscard]]
        size_t indicesCount() const noexcept;

    private:
        Gfx::VertexBufferObjectType m_vertexBufferObject;
        Gfx::VertexArrayObjectType m_vertexArrayObject;
        Gfx::ElementBufferObjectType m_elementBufferObject;

        size_t m_indicesCount;
    };
} // namespace Emerald
