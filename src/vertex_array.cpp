#include "vertex_array.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(const VertexBuffer& vb)
{
    //
}

void VertexArray::add_index_buffer(const IndexBuffer& ib)
{
    //
}

const std::vector<const VertexBuffer*>& get_vertex_buffers() const
{
    //
}

const IndexBuffer& get_index_buffer() const
{
    //
}