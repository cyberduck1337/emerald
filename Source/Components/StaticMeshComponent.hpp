#pragma once

#include "Gfx.hpp"

namespace Emerald
{
    class StaticMeshComponent
    {
    public:
        StaticMeshComponent(std::vector<Gfx::Vertex>& vertices, std::vector<Gfx::Triangle>& triangles);
        StaticMeshComponent(std::vector<Gfx::Vertex>&& vertices, std::vector<Gfx::Triangle>&& triangles);

        [[nodiscard]]
        Gfx::VertexBufferObjectType vbo() const;

        [[nodiscard]]
        Gfx::VertexArrayObjectType vao() const;

        [[nodiscard]]
        const std::vector<Gfx::Vertex>& vertices() const;

        [[nodiscard]]
        const std::vector<Gfx::Triangle>& triangles() const;

    private:
        Gfx::VertexBufferObjectType m_vertexBufferObject;
        Gfx::VertexArrayObjectType m_vertexArrayObject;

        std::vector<Gfx::Vertex> m_vertices;
        std::vector<Gfx::Triangle> m_triangles;
    };
} // namespace Emerald
