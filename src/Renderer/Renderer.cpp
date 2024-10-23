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
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    m_VAO.bind();

    m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    m_VBO->Bind();

    m_IBO.reset(IndexBuffer::Create(indices, 6));
    m_IBO->Bind();

    m_VBO->Unbind();
    m_VAO.unbind();
    m_IBO->Unbind();

    // default shader
    m_Shader = Global::ResourceManager::GetInstance().LoadShader("src/Shaders/vertex.vs", "src/Shaders/fragment.fs", nullptr, "sprite");
    m_Shader->use();
}

void Renderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color /*, Shader& shader*/)
{
    m_VAO.bind();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_VAO.unbind();
}