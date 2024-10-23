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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    
    m_VAO.bind();

    m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VBO->Bind();

    m_VBO->Unbind();
    m_VAO.unbind();

    // default shader
    m_Shader = Global::ResourceManager::GetInstance().LoadShader("src/Shaders/vertex.vs", "src/Shaders/fragment.fs", nullptr, "sprite");
    m_Shader->use();
}

void Renderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color /*, Shader& shader*/)
{
    m_VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_VAO.unbind();
}