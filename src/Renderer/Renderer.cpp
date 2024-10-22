#include "Renderer/Renderer.h"
#include "ResourceManager.h"

Renderer::Renderer()
{
    InitData();
}

Renderer::~Renderer()
{
}

void Renderer::InitData()
{
    float vertices[] = 
    {
        // pos    
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    };
    
    vao.bind();

    m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VBO->Bind();

    m_VBO->Unbind();
    vao.unbind();
}

void Renderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color /*, Shader& shader*/)
{
    // default shader
    shader = Global::ResourceManager::GetInstance().LoadShader("Shaders/vertex.vs", "Shaders/fragment.fs", nullptr, "sprite");
    shader->use();
    
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.unbind();
}