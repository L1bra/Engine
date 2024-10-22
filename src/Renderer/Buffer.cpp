#include "Renderer/Buffer.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


VertexBuffer* VertexBuffer::Create(uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None: return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(size);
    }
    return nullptr;
}

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None: return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
    }
    return nullptr;
}


// IndexBuffer

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None: return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
    }
    return nullptr;
}
