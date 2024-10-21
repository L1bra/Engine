#include "Renderer.h"
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

    VertexBuffer vbo(vertices, sizeof(vertices));
    vbo.bind();

    vbo.unbind();
    vao.unbind();
}

void Renderer::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color /*, Shader& shader*/)
{
    // default shader
    shader = Global::ResourceManager::GetInstance().LoadShader("shaders/vertex.vs", "src/shaders/fragment.fs", nullptr, "sprite");
    shader->use();
    
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.unbind();
}