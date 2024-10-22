#pragma once


#include <stdint.h>


struct IBuffer
{
    virtual size_t Size() const = 0;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual ~IBuffer() = default;
};

struct VertexBuffer : public IBuffer
{
public:
    //virtual size_t Size() const = 0;

    //virtual void Bind() const = 0;
    //virtual void Unbind() const = 0;

    static VertexBuffer* Create(uint32_t size);
    static VertexBuffer* Create(float* vertices, uint32_t size);
};

struct IndexBuffer : public IBuffer
{
public:
    //virtual size_t Size() const = 0;

    //virtual void Bind() const = 0;
    //virtual void Unbind() const = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t count);
};