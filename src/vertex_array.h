#pragma once

#include "buffer.h"
// #include <vector>

struct IVertexArray
{
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(const VertexBuffer& vb) = 0;
    virtual void add_index_buffer(const IndexBuffer& ib) = 0;

    // virtual const std::vector<const VertexBuffer*>& get_vertex_buffers() const = 0;
    // virtual const IndexBuffer& get_index_buffer() const = 0;

    virtual ~IVertexArray() = default;
};


struct VertexArray : public IVertexArray
{
    unsigned int m_id = 0;
public:
    VertexArray();
    ~VertexArray();

    void bind() const override;
    void unbind() const override;

    void add_vertex_buffer(const VertexBuffer& vb) override;
    void add_index_buffer(const IndexBuffer& ib) override;

};