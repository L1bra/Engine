#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(const unsigned size)
    :
    m_size(size)
{
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const float* data, const unsigned size)
    :
    m_id(0),
    m_vbo(0),
    m_size(size)
{
    glCreateBuffers(1, &m_id);
    //glBindBuffer(1, m_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW);

    //TODO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}


void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, unsigned size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


inline size_t OpenGLVertexBuffer::Size() const
{
    return m_size;
}




OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    :
    m_count(count)
{
    glCreateBuffers(1, &m_id);

    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t OpenGLIndexBuffer::Size() const
{
	return size_t();
}
