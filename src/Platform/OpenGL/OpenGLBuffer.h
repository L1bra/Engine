#pragma once

#include "Renderer/Buffer.h"


class OpenGLVertexBuffer : public VertexBuffer
{
public:
    unsigned int m_id = 0;
    unsigned int m_vbo = 0;
    size_t m_size;
public:
    OpenGLVertexBuffer(const unsigned size);
    OpenGLVertexBuffer(const float* data, const unsigned size);
    virtual ~OpenGLVertexBuffer();

    void Bind() const override;
    void Unbind() const override;

    void SetData(const void* data, unsigned size);

    size_t Size() const override;
};


struct OpenGLIndexBuffer : public IndexBuffer
{
    uint32_t m_id = 0;
    unsigned m_ibo = 0;
    unsigned m_count = 0;
public:
    OpenGLIndexBuffer(uint32_t* data, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    void Bind() const override;
    void Unbind() const override;

    size_t Size() const override;
};