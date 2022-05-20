#pragma once

#include "memory.h"

#include <glad/glad.h>

#include <stdint.h>


struct IBuffer
{
    virtual size_t size() const = 0;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual ~IBuffer() = default;
};

struct VertexBuffer : public IBuffer
{
    unsigned int m_id;
    unsigned int m_vbo;
    size_t m_size;
public:
    VertexBuffer(const unsigned size);
    VertexBuffer(const float* data, const unsigned size);
    ~VertexBuffer();

    void bind() override;
    void unbind() override;

    void set_data(const void* data, unsigned size);
    
    size_t size() const override;
};

struct IndexBuffer : public IBuffer
{
    uint32_t m_id;
    unsigned m_ibo;
    unsigned m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() override;
    void unbind() override;

    size_t size() const override;
};