#include "StaticMeshComponent.hpp"

namespace Emerald
{
    StaticMeshComponent::StaticMeshComponent(std::vector<Gfx::Vertex>& vertices, std::vector<Gfx::Triangle>& triangles) : m_vertexBufferObject(Gfx::createVertexBufferObject()), m_vertexArrayObject(Gfx::createVertexArrayObject()), m_vertices(vertices), m_triangles(triangles)
    {
        Gfx::updateVertexBufferData(m_vertexBufferObject, m_vertices);
    }

    StaticMeshComponent::StaticMeshComponent(std::vector<Gfx::Vertex>&& vertices, std::vector<Gfx::Triangle>&& triangles) : m_vertexBufferObject(Gfx::createVertexBufferObject()), m_vertexArrayObject(Gfx::createVertexArrayObject()), m_vertices(std::move(vertices)), m_triangles(std::move(triangles))
    {
        Gfx::updateVertexBufferData(m_vertexBufferObject, m_vertices);
    }

    Gfx::VertexBufferObjectType StaticMeshComponent::vbo() const
    {
        return m_vertexBufferObject;
    }

    Gfx::VertexArrayObjectType StaticMeshComponent::vao() const
    {
        return m_vertexArrayObject;
    }

    const std::vector<Gfx::Vertex>& StaticMeshComponent::vertices() const
    {
        return m_vertices;
    }

    const std::vector<Gfx::Triangle>& StaticMeshComponent::triangles() const
    {
        return m_triangles;
    }
} // namespace Emerald
