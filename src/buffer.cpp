#include "buffer.h"

VertexBuffer::VertexBuffer(const unsigned size)
    :
    m_size(size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(const float* data, const unsigned size)
    :
    m_size(size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(1, m_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW);

    //TODO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}


void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::set_data(const void* data, unsigned size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


inline size_t VertexBuffer::size() const
{
    return m_size;
}


// IndexBuffer

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
    :
    m_count(count)
{
    //
}

IndexBuffer::~IndexBuffer()
{

}

void IndexBuffer::bind()
{

}

void IndexBuffer::unbind()
{

}

inline size_t IndexBuffer::size() const
{
    return m_count;
}