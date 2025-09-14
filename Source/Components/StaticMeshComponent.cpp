#include "StaticMeshComponent.hpp"

namespace Emerald
{
    StaticMeshComponent::StaticMeshComponent(const std::vector<Gfx::Vertex>& vertices, const std::vector<Gfx::Triangle>& triangles) noexcept : m_vertexBufferObject(Gfx::createVertexBufferObject()), m_vertexArrayObject(Gfx::createVertexArrayObject()), m_elementBufferObject(Gfx::createElementBufferObject()), m_indicesCount(triangles.size() * 3)
    {
        Gfx::upload(m_vertexBufferObject, vertices, m_elementBufferObject, triangles);
    }

    StaticMeshComponent::~StaticMeshComponent() noexcept
    {
        Gfx::destroyVertexBufferObject(m_vertexBufferObject);
        Gfx::destroyVertexArrayObject(m_vertexArrayObject);
        Gfx::destroyElementBufferObject(m_elementBufferObject);
    }

    Gfx::VertexBufferObjectType StaticMeshComponent::vbo() const noexcept
    {
        return m_vertexBufferObject;
    }

    Gfx::VertexArrayObjectType StaticMeshComponent::vao() const noexcept
    {
        return m_vertexArrayObject;
    }

    Gfx::ElementBufferObjectType StaticMeshComponent::ebo() const noexcept
    {
        return m_elementBufferObject;
    }

    size_t StaticMeshComponent::indicesCount() const noexcept
    {
        return m_indicesCount;
    }
} // namespace Emerald
